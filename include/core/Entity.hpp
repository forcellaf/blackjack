#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

namespace game {
    namespace core {

        /**
         * @brief Base class for all game entities
         *
         * Provides common functionality for all game objects including:
         * - Unique identification
         * - Active state management
         * - Lifecycle management
         */
        class Entity {
        public:
            /**
             * @brief Construct a new Entity object
             * @param name Optional name for the entity
             */
            explicit Entity(const std::string& name = "Entity")
                : m_name(name), m_active(true), m_id(++s_nextId) {}

            /**
             * @brief Virtual destructor for proper inheritance
             */
            virtual ~Entity() = default;

            /**
             * @brief Update the entity (called each frame)
             * @param deltaTime Time elapsed since last frame in seconds
             */
            virtual void update(float deltaTime) {}

            /**
             * @brief Get the entity's unique ID
             * @return unsigned int The unique ID
             */
            unsigned int getId() const { return m_id; }

            /**
             * @brief Get the entity's name
             * @return const std::string& The name
             */
            const std::string& getName() const { return m_name; }

            /**
             * @brief Set the entity's name
             * @param name The new name
             */
            void setName(const std::string& name) { m_name = name; }

            /**
             * @brief Check if the entity is active
             * @return true if active, false otherwise
             */
            bool isActive() const { return m_active; }

            /**
             * @brief Set the entity's active state
             * @param active The new active state
             */
            void setActive(bool active) { m_active = active; }

        protected:
            std::string m_name;
            bool m_active;
            unsigned int m_id;

        private:
            static unsigned int s_nextId;
        };

    } // namespace core
} // namespace game

#endif // ENTITY_HPP
