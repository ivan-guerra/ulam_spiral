use criterion::BenchmarkId;
use criterion::Criterion;
use criterion::{criterion_group, criterion_main};
use ulam_spiral::generate_ulam_matrix;

pub fn criterion_benchmark(c: &mut Criterion) {
    for n in [128, 256, 512, 1024, 2048, 4096] {
        c.bench_with_input(BenchmarkId::new("generate_ulam_matrix ", n), &n, |b, &n| {
            b.iter(|| generate_ulam_matrix(n));
        });
    }
}

criterion_group!(benches, criterion_benchmark);
criterion_main!(benches);
