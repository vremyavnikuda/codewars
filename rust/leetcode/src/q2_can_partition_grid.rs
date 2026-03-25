impl Solution {
    pub fn can_partition_grid(grid: Vec<Vec<i32>>) -> bool {
        let x = grid.len();
        if x == 0 {
            return false;
        }
        let y = grid[0].len();
        if y == 0 {
            return false;
        }

        let mut t: i64 = 0;
        let mut i = 0usize;
        while i < x {
            let r = &grid[i];
            let mut j = 0usize;
            while j < y {
                t += r[j] as i64;
                j += 1;
            }
            i += 1;
        }

        if (t & 1) != 0 {
            return false;
        }

        let mut p: i64 = 0;
        let mut a = 0usize;
        while a < x {
            let r = &grid[a];
            let mut b = 0usize;
            while b < y {
                p += r[b] as i64;
                b += 1;
            }
            if (p << 1) == t && a + 1 < x {
                return true;
            }
            a += 1;
        }

        p = 0;
        let mut c = 0usize;
        while c < y {
            let mut d = 0usize;
            while d < x {
                p += grid[d][c] as i64;
                d += 1;
            }
            if (p << 1) == t && c + 1 < y {
                return true;
            }
            c += 1;
        }

        false
    }
}
