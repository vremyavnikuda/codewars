impl Solution {
    pub fn remove_covered_intervals(intervals: Vec<Vec<i32>>) -> i32 {
        let mut q1 = intervals;
        q1.sort_unstable_by(|a, b| {
            if a[0] == b[0] {
                b[1].cmp(&a[1])
            } else {
                a[0].cmp(&b[0])
            }
        });
        let mut a1 = 0i32;
        let mut q2 = i32::MIN;
        for q3 in &q1 {
            let a2 = q3[1];
            if a2 > q2 {
                a1 += 1;
                q2 = a2;
            }
        }
        a1
    }
}
