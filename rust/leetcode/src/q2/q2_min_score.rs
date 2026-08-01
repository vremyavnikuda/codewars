impl Solution {
    pub fn min_score(n: i32, roads: Vec<Vec<i32>>) -> i32 {
        let q1 = n as usize;
        let mut q2 = vec![vec![]; q1 + 1];
        for a1 in &roads {
            let a2 = a1[0] as usize;
            let a3 = a1[1] as usize;
            let a4 = a1[2];
            q2[a2].push((a3, a4));
            q2[a3].push((a2, a4));
        }
        let mut q3 = vec![false; q1 + 1];
        let mut q4 = i32::MAX;
        fn q5(a2: usize, q2: &[Vec<(usize, i32)>], q3: &mut [bool], q4: &mut i32) {
            q3[a2] = true;
            for &(a3, a4) in &q2[a2] {
                *q4 = (*q4).min(a4);
                if !q3[a3] {
                    q5(a3, q2, q3, q4);
                }
            }
        }
        q5(1, &q2, &mut q3, &mut q4);
        q4
    }
}