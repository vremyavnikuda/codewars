impl Solution {
    pub fn min_number_operations(target: Vec<i32>) -> i32 {
        if target.is_empty() {
            return 0;
        }
        let mut t1 = target[0];
        for na1 in 1..target.len() {
            if target[na1] > target[na1 - 1] {
                t1 += target[na1] - target[na1 - 1];
            }
        }
        t1
    }
}