impl Solution {
    pub fn stone_game_v(stone_value: Vec<i32>) -> i32 {
        let n = stone_value.len();
        let mut s = vec![0i32; n + 1];
        for i in 0..n {
            s[i + 1] = s[i] + stone_value[i];
        }
        let mut f = vec![vec![-1i32; n]; n];
        fn dfs(
            stone_value: &[i32],
            s: &[i32],
            f: &mut Vec<Vec<i32>>,
            i: usize,
            j: usize,
        ) -> i32 {
            if i >= j {
                return 0;
            }
            if f[i][j] != -1 {
                return f[i][j];
            }
            let mut ans = 0i32;
            let mut l = 0i32;
            let mut r = s[j + 1] - s[i];
            for k in i..j {
                l += stone_value[k];
                r -= stone_value[k];
                if l < r {
                    if ans > l * 2 {
                        continue;
                    }
                    ans = ans.max(l + dfs(stone_value, s, f, i, k));
                } else if l > r {
                    if ans > r * 2 {
                        break;
                    }
                    ans = ans.max(r + dfs(stone_value, s, f, k + 1, j));
                } else {
                    ans = ans.max(l + dfs(stone_value, s, f, i, k));
                    ans = ans.max(r + dfs(stone_value, s, f, k + 1, j));
                }
            }
            f[i][j] = ans;
            ans
        }
        dfs(&stone_value, &s, &mut f, 0, n - 1)
    }
}
