impl Solution {
    pub fn climb_stairs(n: i32, costs: Vec<i32>) -> i32 {
        if n <= 0 {
            return 0;
        }
        let mut f = std::iter::once(0)
            .chain(std::iter::repeat(i32::MAX / 2).take(n.try_into().unwrap()))
            .collect::<Vec<_>>();
        for i in 1..=n as usize {
            let x = costs[i - 1];
            for j in i.saturating_sub(3)..i {
                f[i] = f[i].min(f[j] + x + ((i - j) * (i - j)) as i32);
            }
        }
        f[n as usize]
    }
}
