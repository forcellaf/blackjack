#ifndef VIEW_HPP
#define VIEW_HPP

#include "core/Entity.hpp"
#include "models/Model.hpp"
#include <memory>

namespace game {
    namespace views {

        /**
         * @brief Base class for all game views
         *
         * The View component in MVC architecture.
         * Handles rendering and visual representation.
         * Views should observe Models and render their state.
         */
        class View : public core::Entity {
        public:
            /**
             * @brief Construct a new View object
             * @param name Optional name for the view
             */
            explicit View(const std::string& name = "View")
                : core::Entity(name) {}

            /**
             * @brief Virtual destructor
             */
            virtual ~View() = default;

            /**
             * @brief Initialize the view
             *
             * Set up rendering resources, load assets, etc.
             */
            virtual void init() {}

            /**
             * @brief Render the view
             *
             * Called each frame to render the view's content.
             * Subclasses should implement this to draw their specific content.
             */
            virtual void render() = 0;

            /**
             * @brief Update the view (for animations, etc.)
             * @param deltaTime Time elapsed since last frame
             */
            virtual void update(float deltaTime) override {}

        };

    } // namespace views
} // namespace game

#endif // VIEW_HPP
