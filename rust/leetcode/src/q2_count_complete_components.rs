impl Solution {
    pub fn count_complete_components(n: i32, edges: Vec<Vec<i32>>) -> i32 {
        let n = n as usize;
        let mut q1 = vec![vec![]; n];
        for q2 in &edges {
            let q3 = q2[0] as usize;
            let q4 = q2[1] as usize;
            q1[q3].push(q4);
            q1[q4].push(q3);
        }
        let mut q5 = vec![false; n];
        let mut q6 = 0;
        for a1 in 0..n {
            if !q5[a1] {
                let mut a2 = vec![a1];
                q5[a1] = true;
                let mut a3 = 0;
                let mut a4 = 0;
                while let Some(a5) = a2.pop() {
                    a4 += 1;
                    a3 += q1[a5].len();
                    for &a6 in &q1[a5] {
                        if !q5[a6] {
                            q5[a6] = true;
                            a2.push(a6);
                        }
                    }
                }
                if a4 * (a4 - 1) == a3 {
                    q6 += 1;
                }
            }
        }
        q6
    }
}
