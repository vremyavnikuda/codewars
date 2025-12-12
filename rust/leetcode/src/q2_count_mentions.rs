struct Solution;

impl Solution {
    pub fn count_mentions(number_of_users: i32, events: Vec<Vec<String>>) -> Vec<i32> {
        let mut e = events;
        e.sort_by(|a, b| {
            let ta = a[1].parse::<i32>().unwrap();
            let tb = b[1].parse::<i32>().unwrap();

            if ta == tb {
                a[0].as_bytes()[2].cmp(&b[0].as_bytes()[2])
            } else {
                ta.cmp(&tb)
            }
        });

        let n = number_of_users as usize;
        let mut m = vec![0; n];
        let mut o = vec![0; n];
        let mut p = 0;

        for ev in &e {
            let t = ev[0].as_str();
            let c = ev[1].parse::<i32>().unwrap();
            let d = &ev[2];

            if t.as_bytes()[2] == b'F' {
                let u = d.parse::<usize>().unwrap();
                o[u] = c + 60;
            } else if d.as_bytes()[0] == b'A' {
                p += 1;
            } else if d.as_bytes()[0] == b'H' {
                for u in 0..n {
                    if o[u] <= c {
                        m[u] += 1;
                    }
                }
            } else {
                for s in d.split_whitespace() {
                    let u = s[2..].parse::<usize>().unwrap();
                    m[u] += 1;
                }
            }
        }

        if p > 0 {
            for u in 0..n {
                m[u] += p;
            }
        }

        m
    }
}

fn main() {
    let r1 = Solution::count_mentions(
        3,
        vec![
            vec!["MESSAGE".to_string(), "10".to_string(), "ALL".to_string()],
            vec!["OFFLINE".to_string(), "5".to_string(), "0".to_string()],
            vec!["MESSAGE".to_string(), "20".to_string(), "HERE".to_string()],
        ],
    );
    println!("{:?}", r1);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(
            Solution::count_mentions(
                3,
                vec![
                    vec!["MESSAGE".to_string(), "10".to_string(), "ALL".to_string()],
                    vec!["OFFLINE".to_string(), "5".to_string(), "0".to_string()],
                    vec!["MESSAGE".to_string(), "20".to_string(), "HERE".to_string()],
                ],
            ),
            vec![2, 2, 2]
        );
    }

    #[test]
    fn t2() {
        assert_eq!(
            Solution::count_mentions(
                2,
                vec![
                    vec!["MESSAGE".to_string(), "0".to_string(), "id0".to_string()],
                    vec!["OFFLINE".to_string(), "1".to_string(), "0".to_string()],
                    vec!["MESSAGE".to_string(), "2".to_string(), "HERE".to_string()],
                ],
            ),
            vec![1, 1]
        );
    }

    #[test]
    fn t3() {
        assert_eq!(
            Solution::count_mentions(
                3,
                vec![
                    vec![
                        "MESSAGE".to_string(),
                        "5".to_string(),
                        "id0 id1".to_string()
                    ],
                    vec!["MESSAGE".to_string(), "10".to_string(), "ALL".to_string()],
                ],
            ),
            vec![2, 2, 1]
        );
    }
}
