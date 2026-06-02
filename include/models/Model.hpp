#ifndef MODEL_HPP
#define MODEL_HPP

#include "core/Entity.hpp"

namespace game {
    namespace models {

        /**
         * @brief Base class for all game models
         *
         * The Model component in MVC architecture.
         * Handles data, game state, and business logic.
         * Models should NOT handle rendering or input directly.
         */
        class Model : public core::Entity {
        public:
            /**
             * @brief Construct a new Model object
             * @param name Optional name for the model
             */
            explicit Model(const std::string& name = "Model")
                : core::Entity(name) {}

            /**
             * @brief Virtual destructor
             */
            virtual ~Model() = default;

            /**
             * @brief Initialize the model
             *
             * Called once when the model is first created.
             * Set up initial state and data here.
             */
            virtual void init() {}

            /**
             * @brief Update the model state
             * @param deltaTime Time elapsed since last frame
             *
             * Update model-specific logic and data.
             */
            virtual void update(float deltaTime) override {}

            /**
             * @brief Reset the model to initial state
             */
            virtual void reset() {}

        };

    } // namespace models
} // namespace game

#endif // MODEL_HPP
