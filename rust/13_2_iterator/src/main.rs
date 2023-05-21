fn main() {
    let v1 = vec![1, 2, 3];
    let v1_iter = v1.iter(); // v1_iter is an iterator
    
    for i in v1_iter {
        println!("{i}");
    }

    let v2: Vec<i32> = vec![1, 2, 3];
    let v3: Vec<_> = v2.iter().map(|x| {
        let mut result: i32 = *x;
        if x % 2 == 0 {
            result *= 10;
        }    
        return result;
    }).collect();

    for i in v3.iter() {
        println!("{i}");
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_next_method() {
        let vec = vec![1, 2, 3];
        let mut vec_iter = vec.iter();

        assert_eq!(vec_iter.next(), Some(&1));
        assert_eq!(vec_iter.next(), Some(&2));
        assert_eq!(vec_iter.next(), Some(&3));
        assert_eq!(vec_iter.next(), None);
    }

    #[test]
    fn test_consuming_adaptors() {
        /* method that consumes iterators */
        let vec = vec![1, 2, 3]; 
        let vec_iter = vec.iter();
        let total: i32 = vec_iter.sum();
        assert_eq!(total, 6);
    }
}
