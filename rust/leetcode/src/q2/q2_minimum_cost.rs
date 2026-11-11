impl Solution {
    pub fn minimum_cost(cost1: i32, cost2: i32, cost_both: i32, need1: i32, need2: i32) -> i64 {
        let aa = need1 as i64 * cost1 as i64 + need2 as i64 * cost2 as i64;
        let bb = cost_both as i64 * need1.max(need2) as i64;
        let dd = need1.min(need2);
        let cc = cost_both as i64 * dd as i64
            + (need1 - dd) as i64 * cost1 as i64
            + (need2 - dd) as i64 * cost2 as i64;
        aa.min(bb).min(cc)
    }
}
