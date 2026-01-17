struct Solution;

impl Solution {
    pub fn largest_square_area(bottom_left: Vec<Vec<i32>>, top_right: Vec<Vec<i32>>) -> i64 {
        let n = bottom_left.len();
        if n < 2 {
            return 0;
        }
        let mut best = 0i32;
        let bl = bottom_left.as_slice();
        let tr = top_right.as_slice();
        unsafe {
            for i in 0..(n - 1) {
                let bi = bl.get_unchecked(i);
                let ti = tr.get_unchecked(i);
                let x1 = *bi.get_unchecked(0);
                let y1 = *bi.get_unchecked(1);
                let x2 = *ti.get_unchecked(0);
                let y2 = *ti.get_unchecked(1);
                for j in (i + 1)..n {
                    let bj = bl.get_unchecked(j);
                    let tj = tr.get_unchecked(j);
                    let x3 = *bj.get_unchecked(0);
                    let y3 = *bj.get_unchecked(1);
                    let x4 = *tj.get_unchecked(0);
                    let y4 = *tj.get_unchecked(1);
                    let w = if x2 < x4 { x2 } else { x4 }
                        - if x1 > x3 { x1 } else { x3 };
                    if w <= best {
                        continue;
                    }
                    let h = if y2 < y4 { y2 } else { y4 }
                        - if y1 > y3 { y1 } else { y3 };
                    if h <= best {
                        continue;
                    }
                    let e = if w < h { w } else { h };
                    if e > best {
                        best = e;
                    }
                }
            }
        }
        let b = best as i64;
        b * b
    }
}
