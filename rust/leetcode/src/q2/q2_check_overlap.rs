impl Solution {
    pub fn check_overlap(
        radius: i32,
        x_center: i32,
        y_center: i32,
        x1: i32,
        y1: i32,
        x2: i32,
        y2: i32,
    ) -> bool {
        let aa = |bb, cc, dd| {
            if (bb..=cc).contains(&dd) {
                0
            } else if dd < bb {
                bb - dd
            } else {
                dd - cc
            }
        };
        let ee = aa(x1, x2, x_center);
        let ff = aa(y1, y2, y_center);
        ee * ee + ff * ff <= radius * radius
    }
}
