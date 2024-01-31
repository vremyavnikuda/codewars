package BeginnerSeriesClock

func Past(h, m, s int) int {

	return s*1000 + m*60000 + h*3600000
}

func Rps(p1, p2 string) string {
	switch {
	case p1 == "rock" && p2 == "scissors":
		return "Player 1 won!"
	case p1 == "scissors" && p2 == "paper":
		return "Player 1 won!"
	case p1 == "paper" && p2 == "rock":
		return "Player 1 won!"
	case p2 == "rock" && p1 == "scissors":
		return "Player 2 won!"
	case p2 == "scissors" && p1 == "paper":
		return "Player 2 won!"
	case p2 == "paper" && p1 == "rock":
		return "Player 2 won!"
	case p1 == p2:
		return "Draw!"
	default:
		return "\"Invalid input. Please enter 'rock', 'scissors', or 'paper'.\""
	}
	if p1 == p2 {
		return "Draw!"
	}
}
