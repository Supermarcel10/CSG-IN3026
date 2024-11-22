#pragma once
#include <engine.h>
#include <unordered_map>
#include <string>


namespace engine
{
    // Forward declarations
    class prefab;
    class prefab_manager;

    struct prefab_instance
    {
        ref<game_object> object;
        glm::vec3 position;
        glm::vec3 rotation_axis;
        float rotation_amount;
        glm::vec3 scale;

        prefab_instance(const ref<game_object>& obj,
                        const glm::vec3& pos,
                        const glm::vec3& rot_axis,
                        float rot_amount,
                        const glm::vec3& scl)
                : object(obj)
                , position(pos)
                , rotation_axis(rot_axis)
                , rotation_amount(rot_amount)
                , scale(scl) {}
    };

    struct instance_data
    {
        glm::mat4 transform;
        ref<game_object> object;

        instance_data(const glm::mat4& t, const ref<game_object>& obj) : transform(t), object(obj) {}
    };

    class prefab
    {
    private:
        std::string m_name;
        game_object_properties m_properties;
        ref<material> m_material;
        std::vector<ref<texture_2d>> m_textures;
        std::vector<ref<prefab_instance>> m_instances;

    public:
        static ref<prefab> create(
                const std::string& name,
                const game_object_properties& props,
                const ref<material>& material,
                const std::vector<ref<texture_2d>>& textures)
        {
            return std::make_shared<prefab>(name, props, material, textures);
        }

        static ref<prefab> create(
                const std::string& name,
                const game_object_properties& props)
        {
            return std::make_shared<prefab>(name, props);
        }

        prefab(const std::string& name,
               const game_object_properties& props,
               const ref<material>& material,
               const std::vector<ref<texture_2d>>& textures)
               : m_name(name)
               , m_properties(props)
               , m_material(material)
               , m_textures(textures) {}

        prefab(const std::string& name,
               const game_object_properties& props)
               : m_name(name)
               , m_properties(props) {}

        ref<game_object> instantiate(
                const glm::vec3& position = glm::vec3(0.f),
                const glm::vec3& rotation = glm::vec3(0.f),
                const glm::vec3& scale = glm::vec3(1.f))
        {
            game_object_properties instance_props = m_properties;

            // Apply instance-specific transformations
            instance_props.position = position; //? TODO: Check if this shouldn't be added instead?

            if (rotation != glm::vec3(0.f)) {
                instance_props.rotation_axis = glm::normalize(rotation);
                instance_props.rotation_amount = glm::length(rotation);
            }

            if (scale != glm::vec3(1.f)) {
                instance_props.scale *= scale;
            }

            return game_object::create(instance_props);
        }

        void submit_material(const ref<shader>& shader) const
        {
            if (m_material)
            {
                m_material->submit(shader);
            }
        }

        ref<prefab_instance> create_instance(
                const glm::vec3& position = glm::vec3(0.f),
                const glm::vec3& rotation = glm::vec3(0.f),
                const glm::vec3& scale = glm::vec3(1.f))
        {
            auto game_obj = instantiate(position, rotation, scale);
            auto instance = std::make_shared<prefab_instance>(
                    game_obj,
                    position,
                    rotation != glm::vec3(0.f) ? glm::normalize(rotation) : m_properties.rotation_axis,
                    rotation != glm::vec3(0.f) ? glm::length(rotation) : m_properties.rotation_amount,
                    scale != glm::vec3(1.f) ? scale * m_properties.scale : m_properties.scale
            );

            m_instances.push_back(instance);
            return instance;
        }

        void render_instances(const ref<shader>& shader)
        {
            if (m_instances.empty()) return;

            submit_material(shader);

            for (const auto& instance : m_instances)
            {
                glm::mat4 transform(1.0f);
                transform = glm::translate(transform, instance->position);
                transform = glm::rotate(transform, instance->rotation_amount, instance->rotation_axis);
                transform = glm::scale(transform, instance->scale);

                engine::renderer::submit(shader, transform, instance->object);
            }
        }

        void remove_instance(const ref<prefab_instance>& instance)
        {
            m_instances.erase(
                    std::remove_if(
                            m_instances.begin(),
                            m_instances.end(),
                            [&instance](const ref<prefab_instance>& i)
                            { return i == instance; }),
                    m_instances.end()
            );
        }

        void clear_instances() {
            m_instances.clear();
        }

        const std::vector<ref<prefab_instance>>& get_instances() const {
            return m_instances;
        }

        const std::string& name() const { return m_name; }
        const game_object_properties& properties() const { return m_properties; }
        const ref<material>& material() const { return m_material; }
        const std::vector<ref<texture_2d>>& textures() const { return m_textures; }
    };

    class prefab_manager {
    private:
        std::unordered_map<std::string, ref<prefab>> m_prefabs;

    public:
        static prefab_manager& instance() {
            static prefab_manager instance;
            return instance;
        }

        ref<prefab> register_prefab(
                const std::string& name,
                const std::string& model_path,
                const std::string& texture_path,
                const glm::vec3& position = glm::vec3(0.f),
                const glm::vec3& rotation_axis = glm::vec3(0.f),
                float rotation_amount = 0.f,
                float scale_factor = 1.f,
                bool is_static = true,
                float shininess = 32.0f,
                const glm::vec3& ambient = glm::vec3(1.0f),
                const glm::vec3& diffuse = glm::vec3(1.0f),
                const glm::vec3& specular = glm::vec3(0.1f),
                float opacity = 1.0f
        ) {
            // Create textures
            std::vector<ref<texture_2d>> textures;
            textures.push_back(texture_2d::create(texture_path, false));

            // Create material
            auto material = engine::material::create(
                    shininess,
                    ambient,
                    diffuse,
                    specular,
                    opacity
            );

            // Load model
            auto model = engine::model::create(model_path);

            // Setup properties
            game_object_properties props;
            props.meshes = model->meshes();
            props.textures = textures;
            props.rotation_axis = rotation_axis;
            props.rotation_amount = rotation_amount;

            float adjusted_scale = scale_factor / glm::max(
                    model->size().x,
                    glm::max(model->size().y, model->size().z)
            );

            props.position = position;
            props.bounding_shape = model->size() / 2.f * adjusted_scale;
            props.scale = glm::vec3(adjusted_scale);
            props.is_static = is_static;

            // Create and register the prefab
            auto new_prefab = prefab::create(name, props, material, textures);
            m_prefabs[new_prefab->name()] = new_prefab;
            return new_prefab;
        }

        ref<prefab> get_prefab(const std::string& name) {
            auto it = m_prefabs.find(name);
            if (it != m_prefabs.end()) {
                return it->second;
            }
            return nullptr;
        }

        const std::unordered_map<std::string, ref<prefab>>& get_all_prefabs() const {
            return m_prefabs;
        }

    private:
        prefab_manager() = default;
    };

    class prefab_renderer {
    public:
        static void render_all(const ref<shader>& shader) {
            auto& prefab_mgr = prefab_manager::instance();
            for (const auto& prefab_pair : prefab_mgr.get_all_prefabs()) {
                prefab_pair.second->render_instances(shader);
            }
        }
    };

}
