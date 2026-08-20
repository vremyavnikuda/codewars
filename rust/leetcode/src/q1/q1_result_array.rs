impl Solution {
    pub fn result_array(nums: Vec<i32>) -> Vec<i32> {
        let mut q1 = nums;
        let mut q2 = Vec::with_capacity(q1.len() - 1);
        let mut q3 = 1;
        let mut q4 = q1[0];
        let mut q5 = q1[1];
        q2.push(q5);
        for q6 in 2..q1.len() {
            let q7 = q1[q6];
            if q4 > q5 {
                q1[q3] = q7;
                q3 += 1;
                q4 = q7;
            } else {
                q2.push(q7);
                q5 = q7;
            }
        }
        q1.truncate(q3);
        q1.extend(q2);
        q1
    }
}
