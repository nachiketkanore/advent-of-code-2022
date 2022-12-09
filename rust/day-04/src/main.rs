#![allow(unused)]
fn main() {}

fn solve_part1(input: &str) -> u32 {
    input
        .lines()
        .into_iter()
        .map(|line| {
            line.split(',').fold(Vec::<u32>::new(), |mut result, half| {
                result.append(
                    &mut half
                        .split('-')
                        .map(|val| val.parse().unwrap())
                        .collect::<Vec<u32>>(),
                );
                result
            })
        })
        .fold(0, |mut ans, vals: Vec<u32>| {
            let (l1, r1, l2, r2) = (vals[0], vals[1], vals[2], vals[3]);
            if l1 <= l2 && r2 <= r1 {
                ans += 1;
            } else if l2 <= l1 && r1 <= r2 {
                ans += 1;
            }
            ans
        })
}

fn solve_part2(input: &str) -> u32 {
    input
        .lines()
        .into_iter()
        .map(|line| {
            line.split(',').fold(Vec::<u32>::new(), |mut result, half| {
                result.append(
                    &mut half
                        .split('-')
                        .map(|val| val.parse().unwrap())
                        .collect::<Vec<u32>>(),
                );
                result
            })
        })
        .fold(0, |mut ans, vals: Vec<u32>| {
            let (l1, r1, l2, r2) = (vals[0], vals[1], vals[2], vals[3]);
            if l1 <= l2 && l2 <= r1 {
                ans += 1;
            } else if l1 <= r2 && r2 <= r1 {
                ans += 1;
            } else if l2 <= l1 && l1 <= r2 {
                ans += 1;
            } else if l2 <= r1 && r1 <= r2 {
                ans += 1;
            }
            ans
        })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part1(input), 2);
    }

    #[test]
    fn samples_part2() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part2(input), 4);
    }

    #[test]
    fn part1() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part1(input), 433);
    }

    #[test]
    fn part2() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part2(input), 852);
    }
}
