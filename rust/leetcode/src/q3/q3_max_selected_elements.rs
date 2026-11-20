impl Solution {
    pub fn max_selected_elements(mut nums: Vec<i32>) -> i32 {
        nums.sort_unstable();
        let mut aa = 1;
        let mut bb = i32::MIN;
        let mut cc = 1;
        let mut dd = 1;
        for &ee in &nums {
            if ee == bb {
                dd = cc + 1;
            } else if ee == bb + 1 {
                cc += 1;
                dd += 1;
            } else if ee == bb + 2 {
                cc = dd + 1;
                dd = 1;
            } else {
                cc = 1;
                dd = 1;
            }
            aa = aa.max(cc).max(dd);
            bb = ee;
        }
        aa
    }
}
