;;;Name:Ruixuan Zhang
;;;Parner: Haibo Liu

;;;Solution to problem 1
(defun index (N L)
(if (endp L)'error
(if (equal (N 1)) (car L)
(let ((x (index (N-1) (cdr L))))x))))

;;;Solution to problem 2
(defun min-first (L)
(if (endp (cdr L)) L
(let ((x (min-first (cdr L))))
(if (< (car L) (car x)) L (cons (car x) (cons (car L) (cdr x)))))))

;;;Solution to problem 3
(defun ssort (L)
(if (endp L) nil
(if (endp (cdr L)) L
(let* ((x (min-first L)) (y (ssort (cdr x))))
(cons (car x)y)))))

;;;Solution to problem 4
(defun qsort (L)
(if (endp L) nil
(let ((PL (my_partition (cdr L) (car L))))
(append (qsort (car PL))
(cons (car L) (qsort (cadr PL)))))))

;;;Solution to problem 5
(defun merge-lists (l1 l2)
(if (endp l1) l2
(if (endp l2) l1
(if (< (car l1) (car l2))
(cons (car l1) (merge-lists (cdr l1) l2))
(cons (car l2) (merge-lists l1 (cdr l2)))))))

;;;Solution to problem 6
(defun msort (L)
(if (endp L) nil
(if (endp (cdr L)) L
(let ((x (my_split_list L)))
(merge-lists (msort (car x)) (msort (cadr x)))))))

;;;Solution to problem 7
(defun remove-adj-dupl (L)
(if (endp L) nil
(let ((x (remove-adj-dupl (cdr L))))
(if (equal (car L) (car x))x
(cons (car L) x)))))

;;;Solution to problem 8
(defun unrepeated-elets (L)
(cond ((endp L) nil)
((or (endp (cdr L))
(not (equal (car L) (cadr L))))
(cons (car L) (unrepeated-elets (cdr L))))
((or (endp (cddr L))
(not (equal (car L) (caddr L))))
(unrepeated-elets (cddr L)))      
(t (unrepeated-elets (cdr L)))))

;;;Solution to problem 9
(defun repeated-elets (l)
(cond ((endp l) nil)
((or (endp (cdr l))
(not (equal (car l) (cadr l))))
(repeated-elets (cdr l)))
((or (endp (cddr l))
(not (equal (car l) (caddr l))))
(cons (car l) (repeated-elets (cddr l))))    
(t (repeated-elets (cdr l)))))

;;;No Solution to problem 10

;;;Solution to problem 11
(defun subset (f l)
(if (endp l) nil 
(let ((x (subset f (cdr l))))
(if (funcall f (car l))
(cons (car l) x)x))))

;;;Solution to problem 12
(defun our-some (f l)
(if (endp l) nil
(let ((x (our-some f (cdr l))))
(if (funcall f (car l))l))))

(defun our-every (f l)
(if (endp l) nil
(let ((x (our-every f (cdr l))))
(if (funcall f (car l)) 'T))))

;;;No Solution to problem 13

;;;No solution to problem 14

;;;Solution to problem 15
(defun tr-add (l n)
(if (endp l) n
(tr-add (cdr l) (+ (car l) n))))

(defun tr-mul (l n)
(if (endp l) n
(tr-mul (cdr l) (* (car l) n))))

(defun tr-fac (l n)
(if (zerop l) n
(tr-fac (- l 1) (* l n))))

(defun slow-primep (n)
(if (equal (mod (tr-fac (- n 1) 1) n)(- n 1))
T
nil))

;;;No solution to problem 16