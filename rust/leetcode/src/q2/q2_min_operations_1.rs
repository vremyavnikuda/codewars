impl Solution {
    pub fn min_operations(s: String) -> i32 {
        let aa = s.as_bytes();
        if aa.is_sorted() {
            return 0;
        }
        let bb = aa.len();
        if bb == 2 {
            return -1;
        }
        let (&cc, &dd) = (aa.iter().min().unwrap(), aa.iter().max().unwrap());
        if aa[0] == cc || aa[bb - 1] == dd {
            return 1;
        }
        if aa[1..bb - 1].iter().any(|&ee| ee == cc || ee == dd) {
            return 2;
        }
        3
    }
}
