struct Solution;

impl Solution {
    pub fn max_profit(
        n: i32,
        present: Vec<i32>,
        future: Vec<i32>,
        hierarchy: Vec<Vec<i32>>,
        budget: i32,
    ) -> i32 {
        let n = n as usize;
        let b = budget as usize;
        let mut g = vec![Vec::new(); n + 1];

        for e in &hierarchy {
            g[e[0] as usize].push(e[1] as usize);
        }

        fn dfs(
            u: usize,
            g: &Vec<Vec<usize>>,
            present: &Vec<i32>,
            future: &Vec<i32>,
            b: usize,
        ) -> Vec<[i32; 2]> {
            let mut nxt = vec![[0, 0]; b + 1];

            for &v in &g[u] {
                let fv = dfs(v, g, present, future, b);

                for j in (0..=b).rev() {
                    for jv in 0..=j {
                        for pre in 0..2 {
                            let val = nxt[j - jv][pre] + fv[jv][pre];
                            if val > nxt[j][pre] {
                                nxt[j][pre] = val;
                            }
                        }
                    }
                }
            }

            let mut f = vec![[0, 0]; b + 1];
            let price = future[u - 1];

            for j in 0..=b {
                for pre in 0..2 {
                    let cost = (present[u - 1] / (pre as i32 + 1)) as usize;

                    if j >= cost {
                        f[j][pre] = nxt[j][0].max(nxt[j - cost][1] + price - cost as i32);
                    } else {
                        f[j][pre] = nxt[j][0];
                    }
                }
            }

            f
        }

        dfs(1, &g, &present, &future, b)[b][0]
    }
}

fn main() {
    let r1 = Solution::max_profit(
        3,
        vec![1, 2, 3],
        vec![2, 3, 4],
        vec![vec![1, 2], vec![1, 3]],
        3,
    );
    println!("{}", r1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::max_profit(
                3,
                vec![1, 2, 3],
                vec![2, 3, 4],
                vec![vec![1, 2], vec![1, 3]],
                3,
            ),
            3
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::max_profit(2, vec![2, 4], vec![3, 5], vec![vec![1, 2]], 3,),
            1
        );
    }

    #[test]
    fn t3() {
        assert_eq!(Solution::max_profit(1, vec![5], vec![10], vec![], 5,), 5);
    }
}
