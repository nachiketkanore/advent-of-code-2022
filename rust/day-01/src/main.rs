fn solve_part1(input: &String) -> i32 {
    let inputs: Vec<&str> = input.split("\n").collect();
    let mut sum = 0;
    let mut ans = 0;
    for s in inputs {
        if s == "" {
            sum = 0;
        } else {
            sum += s.parse::<i32>().unwrap();
            if sum > ans {
                ans = sum;
            }
        }
    }
    dbg!(ans);
    ans
}

fn solve_part2(input: &String) -> i32 {
    let inputs: Vec<&str> = input.split("\n").collect();
    let mut sum = 0;
    let mut sums = vec![];
    for s in inputs {
        if s == "" {
            sums.push(sum);
            sum = 0;
        } else {
            sum += s.parse::<i32>().unwrap();
        }
    }
    if sum > 0 {
        sums.push(sum);
    }
    sums.sort();
    sums.reverse();
    let ans = sums[0] + sums[1] + sums[2];
    dbg!(ans);
    ans
}

fn main() {
    // Day 01
    // ans = 70116
    // ans = 206582
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = std::fs::read_to_string("./data/sample.txt").unwrap();
        assert_eq!(solve_part1(&input), 24000);
    }

    #[test]
    fn samples_part2() {
        let input = std::fs::read_to_string("./data/sample.txt").unwrap();
        assert_eq!(solve_part2(&input), 45000);
    }

    #[test]
    fn part1() {
        let input = std::fs::read_to_string("./data/input.txt").unwrap();
        assert_eq!(solve_part1(&input), 70116);
    }

    #[test]
    fn part2() {
        let input = std::fs::read_to_string("./data/input.txt").unwrap();
        assert_eq!(solve_part2(&input), 206582);
    }
}
