#ifndef GAME_HPP
#define GAME_HPP

#include "models/Model.hpp"
#include "views/View.hpp"
#include "controllers/Controller.hpp"
#include <vector>
#include <memory>
#include <string>

namespace game {
    namespace core {

        /**
         * @brief Main game class managing the game loop and MVC components
         *
         * Singleton pattern for easy access to game-wide functionality.
         * Manages the update loop, rendering, and component coordination.
         */
        class Game {
        public:
            /**
             * @brief Get the singleton instance
             * @return Game& Reference to the game instance
             */
            static Game& getInstance() {
                static Game instance;
                return instance;
            }

            // Delete copy constructor and assignment operator
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            /**
             * @brief Initialize the game
             * @param width Window width
             * @param height Window height
             * @param title Window title
             * @param targetFPS Target frames per second (default 60)
             * @return true if initialization succeeded
             */
            bool init(int width, int height, const std::string& title, int targetFPS = 60);

            /**
             * @brief Run the main game loop
             */
            void run();

            /**
             * @brief Clean up and shutdown the game
             */
            void shutdown();

            /**
             * @brief Check if the game is running
             * @return true if game loop is active
             */
            bool isRunning() const { return m_running; }

            /**
             * @brief Add a model to the game
             * @param model The model to add
             */
            void addModel(std::shared_ptr<models::Model> model);

            /**
             * @brief Add a view to the game
             * @param view The view to add
             */
            void addView(std::shared_ptr<views::View> view);

            /**
             * @brief Add a controller to the game
             * @param controller The controller to add
             */
            void addController(std::shared_ptr<controllers::Controller> controller);

            /**
             * @brief Get window width
             */
            int getWidth() const { return m_width; }

            /**
             * @brief Get window height
             */
            int getHeight() const { return m_height; }

            /**
             * @brief Get delta time for current frame
             */
            float getDeltaTime() const { return m_deltaTime; }

        private:
            Game() : m_running(false), m_width(0), m_height(0), m_deltaTime(0.0f) {}

            void update();
            void render();

            bool m_running;
            int m_width;
            int m_height;
            float m_deltaTime;

            std::vector<std::shared_ptr<models::Model>> m_models;
            std::vector<std::shared_ptr<views::View>> m_views;
            std::vector<std::shared_ptr<controllers::Controller>> m_controllers;
        };

    } // namespace core
} // namespace game

#endif // GAME_HPP
