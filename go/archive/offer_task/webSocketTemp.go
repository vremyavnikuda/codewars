package main

import (
	"log"

	"github.com/fasthttp/websocket"
	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/websocket/v2"
)

func main() {
	app := fiber.New()

	// Маршрут для обработки HTTP запросов
	app.Get("/", func(c *fiber.Ctx) error {
		return c.SendString("Hello, Fiber!")
	})

	// Маршрут для обработки веб-сокет соединений
	app.Get("/ws", websocket.New(func(c *websocket.Conn) {
		for {
			messageType, p, err := c.ReadMessage()
			if err != nil {
				log.Println(err)
				return
			}

			if err := c.WriteMessage(messageType, p); err != nil {
				log.Println(err)
				return
			}
		}
	}))
	// Запуск сервера на порту 3000
	log.Fatal(app.Listen(":3000"))
}
