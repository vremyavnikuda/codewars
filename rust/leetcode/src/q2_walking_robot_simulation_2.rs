struct Robot {
    width: i32,
    height: i32,
    x: i32,
    y: i32,
    dir: usize,
    has_moved: bool,
}

impl Robot {
    fn new(width: i32, height: i32) -> Self {
        Robot {
            width,
            height,
            x: 0,
            y: 0,
            dir: 0, // East
            has_moved: false,
        }
    }

    fn step(&mut self, num: i32) {
        self.has_moved = true;
        let perimeter = 2 * (self.width + self.height - 2);
        let mut steps = num % perimeter;
        if num > 0 && steps == 0 && self.x == 0 && self.y == 0 {
            steps = perimeter;
        }
        let dx = [1, 0, -1, 0];
        let dy = [0, 1, 0, -1];
        for _ in 0..steps {
            let nx = self.x + dx[self.dir];
            let ny = self.y + dy[self.dir];
            if nx >= 0 && nx < self.width && ny >= 0 && ny < self.height {
                self.x = nx;
                self.y = ny;
            } else {
                self.dir = (self.dir + 1) % 4;
                self.x += dx[self.dir];
                self.y += dy[self.dir];
            }
        }
    }

    fn get_pos(&self) -> Vec<i32> {
        vec![self.x, self.y]
    }

    fn get_dir(&self) -> String {
        match self.dir {
            0 => "East".to_string(),
            1 => "North".to_string(),
            2 => "West".to_string(),
            3 => "South".to_string(),
            _ => unreachable!(),
        }
    }
}
