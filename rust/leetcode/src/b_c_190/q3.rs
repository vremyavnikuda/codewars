impl Solution {
    pub fn largest_string(nums: Vec<i32>) -> Vec<String> {
        nums.into_iter()
            .map(|aa| {
                let mut bb = String::with_capacity(
                    (aa >> 25) as usize + (aa & ((1 << 25) - 1)).count_ones() as usize,
                );
                bb.extend(std::iter::repeat_n('z', (aa >> 25) as usize));
                for cc in (0..25).rev() {
                    if aa & (1 << cc) != 0 {
                        bb.push((b'a' + cc as u8) as char);
                    }
                }
                bb
            })
            .collect()
    }
}
