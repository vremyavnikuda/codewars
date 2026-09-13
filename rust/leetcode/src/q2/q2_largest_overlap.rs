impl Solution {
    pub fn largest_overlap(img1: Vec<Vec<i32>>, img2: Vec<Vec<i32>>) -> i32 {
        let aa = img1.len() as i32;
        (-aa + 1..aa)
            .flat_map(|bb| (-aa + 1..aa).map(move |cc| (bb, cc)))
            .map(|(bb, cc)| {
                (0..aa)
                    .flat_map(|dd| (0..aa).map(move |ee| (dd, ee)))
                    .filter(|&(dd, ee)| {
                        let asd = dd + bb;
                        let ff = ee + cc;
                        (0..aa).contains(&asd)
                            && (0..aa).contains(&ff)
                            && img1[dd as usize][ee as usize] == 1
                            && img2[asd as usize][ff as usize] == 1
                    })
                    .count()
            })
            .max()
            .unwrap_or(0) as i32
    }
}
