use std::cmp::{Ordering, Reverse};
use std::collections::{BinaryHeap, VecDeque};
use std::f64;

#[derive(Clone, Debug)]
struct Edge {
    to: usize,
    w: f64,
}

#[derive(Clone, Debug)]
struct Graph {
    n: usize,
    adj: Vec<Vec<Edge>>,
}

impl Graph {
    fn new(n: usize) -> Self {
        Self {
            n,
            adj: vec![Vec::new(); n],
        }
    }
    fn add_edge(&mut self, u: usize, v: usize, w: f64) {
        assert!(u < self.n && v < self.n, "vertex out of range");
        assert!(
            w >= 0.0 && w.is_finite(),
            "non-negative finite weights required"
        );
        self.adj[u].push(Edge { to: v, w });
    }
}

/* Totally ordered wrapper for f64.
Accepts only finite numbers and infinities; comparing NaN will panic. */
#[derive(Copy, Clone, Debug, PartialEq)]
struct OrdF64(f64);
impl Eq for OrdF64 {}
impl PartialOrd for OrdF64 {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        self.0.partial_cmp(&other.0)
    }
}
impl Ord for OrdF64 {
    fn cmp(&self, other: &Self) -> Ordering {
        self.0
            .partial_cmp(&other.0)
            .expect("NaN encountered in OrdF64::cmp")
    }
}

/* Partial priority queue: a min-heap by distance with chunked extraction. */
#[derive(Default)]
struct PartialPQ {
    heap: BinaryHeap<(Reverse<OrdF64>, usize)>,
}
impl PartialPQ {
    fn new() -> Self {
        Self {
            heap: BinaryHeap::new(),
        }
    }
    fn clear(&mut self) {
        self.heap.clear();
    }
    fn push(&mut self, key: f64, v: usize) {
        debug_assert!(key.is_finite() || key.is_infinite());
        self.heap.push((Reverse(OrdF64(key)), v));
    }
    fn pop_min(&mut self) -> Option<(f64, usize)> {
        self.heap.pop().map(|(Reverse(k), v)| (k.0, v))
    }
    fn is_empty(&self) -> bool {
        self.heap.is_empty()
    }
    fn len(&self) -> usize {
        self.heap.len()
    }
    fn extract_k_smallest(&mut self, k: usize) -> Vec<(f64, usize)> {
        let mut out = Vec::with_capacity(k);
        for _ in 0..k {
            if let Some((kmin, v)) = self.pop_min() {
                out.push((kmin, v));
            } else {
                break;
            }
        }
        out
    }
    fn batch_prepend(&mut self, items: &[(f64, usize)]) {
        for &(k, v) in items {
            debug_assert!(k.is_finite() || k.is_infinite());
            self.push(k, v);
        }
    }
}

/* Limited batch relaxations. */
fn limited_relaxations(
    g: &Graph,
    dist: &mut [f64],
    pred: &mut [usize],
    rounds: usize,
    active_seed: &[usize],
) {
    if rounds == 0 || active_seed.is_empty() {
        return;
    }
    let mut q = VecDeque::new();
    let mut inq = vec![false; g.n];
    for &s in active_seed.iter() {
        if dist[s].is_finite() && !inq[s] {
            q.push_back(s);
            inq[s] = true;
        }
    }
    let mut layer = 0usize;
    while layer < rounds && !q.is_empty() {
        let mut next = VecDeque::new();
        while let Some(u) = q.pop_front() {
            inq[u] = false;
            let du = dist[u];
            for e in &g.adj[u] {
                let nd = du + e.w;
                if nd < dist[e.to] {
                    dist[e.to] = nd;
                    pred[e.to] = u;
                    if !inq[e.to] {
                        next.push_back(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        q = next;
        layer += 1;
    }
}

/* Collect frontier below the threshold. */
fn collect_frontier(n: usize, dist: &[f64], done: &[bool], d_upper: f64) -> Vec<usize> {
    let mut f = Vec::new();
    for v in 0..n {
        if !done[v] && dist[v].is_finite() && dist[v] < d_upper {
            f.push(v);
        }
    }
    f
}

/* Heuristic depth along predecessor links. */
fn frontier_depth_to(
    v: usize,
    dist: &[f64],
    pred: &[usize],
    d_anchor: f64,
    guard_limit: usize,
) -> usize {
    let mut steps = 0usize;
    let mut cur = v;
    let mut guard = 0usize;
    while dist[cur].is_finite() && dist[cur] >= 0.0 && dist[cur] >= d_anchor {
        let p = pred[cur];
        if p == cur {
            break;
        }
        cur = p;
        steps += 1;
        guard += 1;
        if guard > guard_limit {
            break;
        }
    }
    steps
}

/* Find pivots. */
fn find_pivots(
    g: &Graph,
    dist: &[f64],
    pred: &[usize],
    done: &[bool],
    d_upper: f64,
    b: usize,
) -> Vec<usize> {
    let guard_limit = 8 * b.max(1);
    let f = collect_frontier(g.n, dist, done, d_upper);
    if f.is_empty() {
        return Vec::new();
    }

    let mut depths = Vec::with_capacity(f.len());
    for &v in &f {
        let unit = 1.0_f64.max(d_upper / (b as f64 + 1.0));
        let d_anchor = (dist[v] / unit).floor() * unit;
        let depth = frontier_depth_to(v, dist, pred, d_anchor, guard_limit);
        depths.push((depth, v));
    }

    depths.sort_by_key(|&(d, _)| usize::MAX - d);
    let mut pivots = Vec::new();
    let mut seen = vec![false; g.n];

    for &(d, v) in &depths {
        if d < b {
            continue;
        }
        let mut u = v;
        let mut k = d;
        while k > 0 {
            let p = pred[u];
            if p == u {
                break;
            }
            u = p;
            k -= 1;
        }
        if !seen[u] {
            pivots.push(u);
            seen[u] = true;
            if pivots.len() == b {
                break;
            }
        }
    }
    pivots
}

/* Bounded Dijkstra with a distance threshold. */
fn dijkstra_bounded(
    g: &Graph,
    dist: &mut [f64],
    pred: &mut [usize],
    done: &mut [bool],
    seeds: &[(usize, f64)],
    d_upper: f64,
    b: usize,
) {
    let mut pq = PartialPQ::new();
    for &(s, ds) in seeds {
        if ds < dist[s] {
            dist[s] = ds;
            pred[s] = s;
        }
        if dist[s].is_finite() && dist[s] < d_upper {
            pq.push(dist[s], s);
        }
    }

    let frontier_cap = (g.n / b.max(1)).max(1);
    let batch_k = b.max(1);

    while !pq.is_empty() {
        if pq.len() > frontier_cap {
            let active: Vec<usize> = collect_frontier(g.n, dist, done, d_upper);
            limited_relaxations(g, dist, pred, b, &active);

            let mut items = Vec::new();
            for v in 0..g.n {
                if !done[v] && dist[v].is_finite() && dist[v] < d_upper {
                    items.push((dist[v], v));
                }
            }
            pq.clear();
            pq.batch_prepend(&items);
        }

        let chunk = pq.extract_k_smallest(batch_k);
        if chunk.is_empty() {
            break;
        }

        for (du, u) in chunk {
            if done[u] {
                continue;
            }
            if du > dist[u] {
                continue;
            }
            if du >= d_upper {
                continue;
            }

            done[u] = true;

            for e in &g.adj[u] {
                if done[e.to] {
                    continue;
                }
                let nd = du + e.w;
                if nd < dist[e.to] && nd < d_upper {
                    dist[e.to] = nd;
                    pred[e.to] = u;
                    pq.push(nd, e.to);
                }
            }
        }
    }
}

/* Recursive BMSSP. */
fn bmssp_recursive(
    g: &Graph,
    dist: &mut [f64],
    pred: &mut [usize],
    done: &mut [bool],
    seeds: &[(usize, f64)],
    d_upper: f64,
    b: usize,
    _depth: usize,
) {
    dijkstra_bounded(g, dist, pred, done, seeds, d_upper, b);

    let mut unfinished = Vec::new();
    for v in 0..g.n {
        if !done[v] && dist[v].is_finite() && dist[v] < d_upper {
            unfinished.push(v);
        }
    }
    if unfinished.is_empty() {
        return;
    }

    let pivots = find_pivots(g, dist, pred, done, d_upper, b);
    if pivots.is_empty() {
        let active = collect_frontier(g.n, dist, done, d_upper);
        limited_relaxations(g, dist, pred, b, &active);
        dijkstra_bounded(g, dist, pred, done, seeds, d_upper, b);
        return;
    }

    for &p in &pivots {
        let base = dist[p];
        if !base.is_finite() {
            continue;
        }

        let mut neigh = Vec::new();
        for e in &g.adj[p] {
            let dv = dist[e.to];
            if dv.is_finite() && dv >= base && dv < d_upper {
                neigh.push(dv);
            }
        }
        for e in &g.adj[p] {
            for ee in &g.adj[e.to] {
                let dv = dist[ee.to];
                if dv.is_finite() && dv >= base && dv < d_upper {
                    neigh.push(dv);
                }
            }
        }
        if neigh.is_empty() {
            bmssp_recursive(g, dist, pred, done, &[(p, base)], d_upper, b, 0);
            continue;
        }
        neigh.sort_by(|a, b| a.partial_cmp(b).unwrap());
        let q_idx = neigh.len().min(b.max(2)) - 1;
        let d_local = neigh[q_idx].min(d_upper);

        bmssp_recursive(g, dist, pred, done, &[(p, base)], d_local, b, 0);
    }

    dijkstra_bounded(g, dist, pred, done, seeds, d_upper, b);
}

/* Outer wrapper. */
fn sssp_research_style(g: &Graph, s: usize, b: usize) -> (Vec<f64>, Vec<usize>) {
    assert!(s < g.n, "invalid source");
    let mut dist = vec![f64::INFINITY; g.n];
    let mut pred = (0..g.n).collect::<Vec<_>>();
    let mut done = vec![false; g.n];
    dist[s] = 0.0;
    pred[s] = s;

    let seeds = vec![(s, 0.0)];
    bmssp_recursive(
        g,
        &mut dist,
        &mut pred,
        &mut done,
        &seeds,
        f64::INFINITY,
        b.max(2),
        0,
    );

    (dist, pred)
}

fn main() {
    let mut g = Graph::new(8);
    g.add_edge(0, 1, 3.0);
    g.add_edge(0, 2, 1.0);
    g.add_edge(2, 1, 1.0);
    g.add_edge(1, 3, 2.0);
    g.add_edge(2, 3, 4.0);
    g.add_edge(3, 4, 2.5);
    g.add_edge(1, 5, 10.0);
    g.add_edge(4, 5, 1.0);
    g.add_edge(2, 6, 2.0);
    g.add_edge(6, 7, 2.0);
    g.add_edge(7, 5, 1.0);

    let b = 16;
    let s = 0usize;

    let (dist, pred) = sssp_research_style(&g, s, b);

    for v in 0..g.n {
        if dist[v].is_finite() {
            print!("dist[{v}] = {:.6}", dist[v]);
        } else {
            print!("dist[{v}] = +INF");
        }
        if dist[v].is_finite() {
            let mut path = Vec::new();
            let mut cur = v;
            let mut guard = 0usize;
            while pred[cur] != cur && guard < 4 * g.n {
                path.push(cur);
                cur = pred[cur];
                guard += 1;
            }
            path.push(cur);
            path.reverse();
            println!("   path = {:?}", path);
        } else {
            println!();
        }
    }
}

// dist[0] = 0.000000   path = [0]
// dist[1] = 2.000000   path = [0, 2, 1]
// dist[2] = 1.000000   path = [0, 2]
// dist[3] = 4.000000   path = [0, 2, 1, 3]
// dist[4] = 6.500000   path = [0, 2, 1, 3, 4]
// dist[5] = 6.000000   path = [0, 2, 6, 7, 5]
// dist[6] = 3.000000   path = [0, 2, 6]
// dist[7] = 5.000000   path = [0, 2, 6, 7]

#[cfg(test)]
mod tests {
    use super::*;
    use std::collections::HashSet;
    use std::time::Instant;

    /* Simple deterministic RNG (XorShift64) to avoid external deps. */
    #[derive(Clone)]
    struct XorShift64 {
        state: u64,
    }
    impl XorShift64 {
        fn new(seed: u64) -> Self {
            Self { state: seed.max(1) }
        }
        fn next_u64(&mut self) -> u64 {
            let mut x = self.state;
            x ^= x << 13;
            x ^= x >> 7;
            x ^= x << 17;
            self.state = x;
            x
        }
        fn next_f64_unit(&mut self) -> f64 {
            // Uniform in [0,1)
            const DEN: f64 = (1u64 << 53) as f64;
            ((self.next_u64() >> 11) as f64) / DEN
        }
        fn gen_range_usize(&mut self, lo: usize, hi: usize) -> usize {
            // [lo, hi)
            let span = hi - lo;
            if span == 0 {
                return lo;
            }
            (self.next_u64() as usize % span) + lo
        }
        fn gen_weight(&mut self, max_w: f64) -> f64 {
            // Non-negative finite weights > 0 to avoid ties as much as possible
            let x = self.next_f64_unit();
            let w = x * max_w + 1e-9;
            if w.is_finite() { w } else { max_w }
        }
    }

    /* Baseline Dijkstra with standard min-heap; returns distance vector. */
    fn baseline_dijkstra(g: &Graph, s: usize) -> Vec<f64> {
        let mut dist = vec![f64::INFINITY; g.n];
        let mut done = vec![false; g.n];
        let mut pq: BinaryHeap<(Reverse<OrdF64>, usize)> = BinaryHeap::new();
        dist[s] = 0.0;
        pq.push((Reverse(OrdF64(0.0)), s));

        while let Some((Reverse(OrdF64(d)), u)) = pq.pop() {
            if done[u] {
                continue;
            }
            if d > dist[u] {
                continue;
            }
            done[u] = true;
            for e in &g.adj[u] {
                let nd = d + e.w;
                if nd < dist[e.to] {
                    dist[e.to] = nd;
                    pq.push((Reverse(OrdF64(nd)), e.to));
                }
            }
        }
        dist
    }

    /* Helper: compare two distance arrays with tolerance. */
    fn assert_dist_close(a: &[f64], b: &[f64], eps_abs: f64, eps_rel: f64) {
        assert_eq!(a.len(), b.len(), "distance vector length mismatch");
        for i in 0..a.len() {
            let da = a[i];
            let db = b[i];
            if da.is_infinite() && db.is_infinite() {
                continue;
            }
            let diff = (da - db).abs();
            let scale = da.abs().max(db.abs()).max(1.0);
            assert!(
                diff <= eps_abs || diff / scale <= eps_rel,
                "distance mismatch at {}: got {:.10}, expected {:.10}, |diff|={:.3e}, rel={:.3e}",
                i,
                da,
                db,
                diff,
                diff / scale
            );
        }
    }

    /* Random directed graph generator with exactly m edges, no self-loops, no multi-edges. */
    fn gen_random_graph(n: usize, m: usize, seed: u64, max_w: f64) -> Graph {
        let mut rng = XorShift64::new(seed);
        let mut g = Graph::new(n);
        let mut used = HashSet::<(usize, usize)>::with_capacity(m * 2);
        let mut edges = 0usize;

        while edges < m {
            let u = rng.gen_range_usize(0, n);
            let mut v = rng.gen_range_usize(0, n);
            if v == u {
                v = (v + 1) % n;
            }
            if used.insert((u, v)) {
                let w = rng.gen_weight(max_w);
                g.add_edge(u, v, w);
                edges += 1;
            }
        }
        g
    }

    /* Grid graph N x M with right and down edges; weights in [1, max_w). */
    fn gen_grid_graph(nx: usize, ny: usize, seed: u64, max_w: f64) -> Graph {
        let n = nx * ny;
        let mut rng = XorShift64::new(seed);
        let mut g = Graph::new(n);
        let at = |x: usize, y: usize| -> usize { y * nx + x };
        for y in 0..ny {
            for x in 0..nx {
                let u = at(x, y);
                if x + 1 < nx {
                    let v = at(x + 1, y);
                    g.add_edge(u, v, rng.gen_weight(max_w));
                }
                if y + 1 < ny {
                    let v = at(x, y + 1);
                    g.add_edge(u, v, rng.gen_weight(max_w));
                }
            }
        }
        g
    }

    /* Sanity: small random sparse graphs, multiple seeds. */
    #[test]
    fn random_sparse_small_multiple_seeds() {
        let n = 200;
        let m = 2_000;
        let seeds = [1u64, 12345, 999_001, 2025_08_10, 42];
        for &seed in &seeds {
            let g = gen_random_graph(n, m, seed, 10.0);
            let s = (seed as usize) % n;
            let dist_ref = baseline_dijkstra(&g, s);
            let (dist, _pred) = sssp_research_style(&g, s, 16);
            assert_dist_close(&dist, &dist_ref, 1e-9, 1e-9);
        }
    }

    /* Medium-size dense-ish random graphs. */
    #[test]
    fn random_medium_denser() {
        let n = 400;
        let m = 16_000; // average out-degree 40
        let g = gen_random_graph(n, m, 777, 5.0);
        let s = 7usize;
        let t0 = Instant::now();
        let dist_ref = baseline_dijkstra(&g, s);
        let t1 = Instant::now();
        let (dist, _pred) = sssp_research_style(&g, s, 32);
        let t2 = Instant::now();

        eprintln!(
            "baseline dijkstra: {:?}, research-style: {:?}",
            t1 - t0,
            t2 - t1
        );
        assert_dist_close(&dist, &dist_ref, 1e-9, 1e-9);
    }

    /* Large grid to exercise long paths and structured topology. */
    #[test]
    fn grid_large_structured() {
        let nx = 150;
        let ny = 150;
        let g = gen_grid_graph(nx, ny, 13579, 3.0);
        let s = 0usize; // top-left
        let dist_ref = baseline_dijkstra(&g, s);
        let (dist, _pred) = sssp_research_style(&g, s, 32);
        assert_dist_close(&dist, &dist_ref, 1e-9, 1e-9);
    }

    /* Long chain with shortcuts to test stability on deep predecessor chains. */
    #[test]
    fn long_chain_with_shortcuts() {
        let n = 10_000;
        let mut g = Graph::new(n);
        for i in 0..n - 1 {
            g.add_edge(i, i + 1, 1.0);
        }
        // Random forward shortcuts
        let mut rng = XorShift64::new(2468);
        for _ in 0..n {
            let u = rng.gen_range_usize(0, n - 2);
            let v = rng.gen_range_usize(u + 2, n);
            let w = rng.gen_weight(0.5); // small bonus edges
            g.add_edge(u, v, w);
        }
        let s = 0usize;
        let dist_ref = baseline_dijkstra(&g, s);
        let (dist, _pred) = sssp_research_style(&g, s, 64);
        assert_dist_close(&dist, &dist_ref, 1e-9, 1e-9);
    }

    /* Heavy stress: large n and m. Marked ignored by default; run with:
       cargo test -- --ignored
       or       cargo test heavy_random_stress -- --ignored
    */
    #[test]
    #[ignore]
    fn heavy_random_stress() {
        let n = 5_000;
        let m = 120_000;
        let g = gen_random_graph(n, m, 0xDEADBEEF, 7.0);
        let s = 123usize;
        let t0 = Instant::now();
        let dist_ref = baseline_dijkstra(&g, s);
        let t1 = Instant::now();
        let (dist, _pred) = sssp_research_style(&g, s, 64);
        let t2 = Instant::now();

        eprintln!(
            "n={}, m={}, baseline={:?}, research={:?}",
            n,
            m,
            t1 - t0,
            t2 - t1
        );
        assert_dist_close(&dist, &dist_ref, 1e-8, 1e-8);
    }

    /* Disconnected components: verify +INF handling. */
    #[test]
    fn disconnected_components() {
        let n = 1000;
        let mut g = Graph::new(n);
        // Component A: 0..499
        for i in 0..499 {
            g.add_edge(i, i + 1, 1.0);
        }
        // Component B: 500..999
        for i in 500..999 {
            g.add_edge(i, i + 1, 1.0);
        }
        let s = 0usize;
        let dist_ref = baseline_dijkstra(&g, s);
        let (dist, _pred) = sssp_research_style(&g, s, 16);
        assert_dist_close(&dist, &dist_ref, 1e-9, 1e-9);
        // Spot-check unreachable vertices
        assert!(dist[900].is_infinite());
    }

    /* Random sparse with multiple sources validated one by one. */
    #[test]
    fn random_sparse_multi_sources() {
        let n = 800;
        let m = 8_000;
        let g = gen_random_graph(n, m, 0xABCDEF, 10.0);
        let sources = [0usize, 1, 7, 123, 456, 777];
        for &s in &sources {
            let dist_ref = baseline_dijkstra(&g, s);
            let (dist, _pred) = sssp_research_style(&g, s, 32);
            assert_dist_close(&dist, &dist_ref, 1e-9, 1e-9);
        }
    }

    /* Verify that limited_relaxations never increases distances. */
    #[test]
    fn monotonicity_of_relaxations() {
        let n = 300;
        let m = 4_000;
        let mut g = gen_random_graph(n, m, 314159, 4.0);
        // add a few zero-weight edges to test boundary
        for i in 0..50 {
            let u = i;
            let v = (i + 1) % n;
            g.add_edge(u, v, 0.0);
        }
        let s = 5usize;
        let mut dist = vec![f64::INFINITY; n];
        let mut pred = (0..n).collect::<Vec<_>>();
        let done = vec![false; n];
        dist[s] = 0.0;
        pred[s] = s;

        let before = dist.clone();
        let active = collect_frontier(n, &dist, &done, f64::INFINITY);
        limited_relaxations(&g, &mut dist, &mut pred, 8, &active);

        for i in 0..n {
            assert!(dist[i] <= before[i] || before[i].is_infinite());
        }
    }
}
