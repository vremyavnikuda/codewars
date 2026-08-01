use std::collections::HashMap;

struct Solution;

impl Solution {
    pub fn count_covered_buildings(n: i32, buildings: Vec<Vec<i32>>) -> i32 {
        let mut bx: HashMap<i32, Vec<i32>> = HashMap::new();
        let mut by: HashMap<i32, Vec<i32>> = HashMap::new();

        for b in &buildings {
            let x = b[0];
            let y = b[1];
            bx.entry(x).or_insert_with(Vec::new).push(y);
            by.entry(y).or_insert_with(Vec::new).push(x);
        }

        for v in bx.values_mut() {
            v.sort_unstable();
        }

        for v in by.values_mut() {
            v.sort_unstable();
        }

        let mut c = 0;

        for b in &buildings {
            let x = b[0];
            let y = b[1];

            let ys = &bx[&x];
            let xs = &by[&y];

            let l = xs[0] < x;
            let r = x < xs[xs.len() - 1];
            let d = ys[0] < y;
            let u = y < ys[ys.len() - 1];

            if l && r && d && u {
                c += 1;
            }
        }

        c
    }
}

fn main() {
    let r1 = Solution::count_covered_buildings(
        5,
        vec![
            vec![0, 0],
            vec![1, 1],
            vec![2, 2],
            vec![1, 0],
            vec![1, 2],
            vec![0, 1],
            vec![2, 1],
        ],
    );
    println!("{}", r1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::count_covered_buildings(
                5,
                vec![
                    vec![0, 0],
                    vec![1, 1],
                    vec![2, 2],
                    vec![1, 0],
                    vec![1, 2],
                    vec![0, 1],
                    vec![2, 1]
                ],
            ),
            1
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::count_covered_buildings(3, vec![vec![0, 0], vec![1, 1], vec![2, 2]],),
            0
        );
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::count_covered_buildings(
                3,
                vec![
                    vec![0, 0],
                    vec![0, 1],
                    vec![0, 2],
                    vec![1, 0],
                    vec![1, 1],
                    vec![1, 2],
                    vec![2, 0],
                    vec![2, 1],
                    vec![2, 2]
                ],
            ),
            1
        );
    }
}
