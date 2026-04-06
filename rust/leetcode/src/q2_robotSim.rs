pub struct Solution;
impl Solution {
    pub fn robot_sim(commands: Vec<i32>, obstacles: Vec<Vec<i32>>) -> i32 {
        let dirs = [0, 1, 0, -1, 0];
        let f = |x: i32, y: i32| x * 60010 + y;
        let mut s = std::collections::HashSet::new();
        for e in &obstacles {
            s.insert(f(e[0], e[1]));
        }
        let mut ans = 0;
        let mut k = 0;
        let mut x = 0;
        let mut y = 0;
        for c in commands {
            if c == -2 {
                k = (k + 3) % 4;
            } else if c == -1 {
                k = (k + 1) % 4;
            } else {
                let mut c = c;
                while c > 0 {
                    c -= 1;
                    let nx = x + dirs[k];
                    let ny = y + dirs[k + 1];
                    if s.contains(&f(nx, ny)) {
                        break;
                    }
                    x = nx;
                    y = ny;
                    ans = ans.max(x * x + y * y);
                }
            }
        }
        ans
    }
}
