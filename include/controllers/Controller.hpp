#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "core/Entity.hpp"
#include "models/Model.hpp"
#include "views/View.hpp"
#include <memory>

namespace game {
    namespace controllers {

        /**
         * @brief Base class for all game controllers
         *
         * The Controller component in MVC architecture.
         * Handles input, user interaction, and coordinates between Model and View.
         */
        class Controller : public core::Entity {
        public:
            /**
             * @brief Construct a new Controller object
             * @param name Optional name for the controller
             */
            explicit Controller(const std::string& name = "Controller")
                : core::Entity(name) {}

            /**
             * @brief Virtual destructor
             */
            virtual ~Controller() = default;

            /**
             * @brief Initialize the controller
             *
             * Set up input handlers and initial controller state.
             */
            virtual void init() {}

            /**
             * @brief Handle input events
             *
             * Process user input and update models/views accordingly.
             */
            virtual void handleInput() = 0;

            /**
             * @brief Update the controller
             * @param deltaTime Time elapsed since last frame
             */
            virtual void update(float deltaTime) override {}

        };

    } // namespace controllers
} // namespace game

#endif // CONTROLLER_HPP
