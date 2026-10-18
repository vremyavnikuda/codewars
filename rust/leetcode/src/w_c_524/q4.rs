impl Solution {
    pub fn min_selection(
        available_intervals: Vec<Vec<i32>>,
        target_intervals: Vec<Vec<i32>>,
    ) -> i32 {
        const MAX: usize = 100_001;
        let mut reach = vec![0i32; MAX + 1];
        for a in &available_intervals {
            let s = a[0] as usize;
            reach[s] = reach[s].max(a[1]);
        }
        for i in 1..=MAX {
            reach[i] = reach[i].max(reach[i - 1]);
        }
        let mut targets = target_intervals;
        targets.sort_unstable_by_key(|t| t[0]);
        let (mut cur, mut cnt) = (0i32, 0i32);
        for t in &targets {
            while cur < t[1] {
                let x = cur.max(t[0]);
                let best = reach[x as usize];
                if best < x || best <= cur {
                    return -1;
                }
                cur = best;
                cnt += 1;
            }
        }
        cnt
    }
}
