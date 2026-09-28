impl Solution {
    pub fn max_depth(s: String) -> i32 {
        s.bytes()
            .fold((0, 0), |(aa, bb), cc| match cc {
                b'(' => (aa.max(bb + 1), bb + 1),
                b')' => (aa, bb - 1),
                _ => (aa, bb),
            })
            .0
    }
}
