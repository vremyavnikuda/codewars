impl Solution {
    #[inline(always)]
    pub fn sort_by_bits(arr: Vec<i32>) -> Vec<i32> {
        let mut arr = arr;
        let (_0, _1) = (14i32, (1i32 << 14) - 1);
        let mut _2 = 0usize;
        while _2 < arr.len() {
            let _3 = arr[_2];
            arr[_2] = ((_3 as u32).count_ones() as i32).wrapping_shl(_0 as u32) | _3;
            _2 += 1;
        }
        arr.sort_unstable();
        let mut _4 = 0usize;
        while _4 < arr.len() {
            arr[_4] &= _1;
            _4 += 1;
        }
        arr
    }
}
