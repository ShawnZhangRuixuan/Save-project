;;; Name: Ruixuan Zhang
;;; My Partner: Haibo Liu

;;;Solution to problem 1
(defun MY_SUM(L)
(if (endp L) 0 (let ((x (MY_SUM (cdr L))))
(+ (car L) x))))

;;;Solution to problem 2
(defun neg-nums(L)
(cond ((endp L) Nil)
((minusp (car L)) (cons (car L) (neg-nums (cdr L))))
(t (neg-nums (cdr L)))))

;;;Solution to problem 3
(defun my_inc-list-2 (L N)
(if (endp L)
Nil
(let ((x (my_inc-list-2 (cdr L) N)))
(cons (+ (car L) N) X))))

;;;Solution to proble 4
(defun myinsert (N L)
(if (endp L)
(list N)
(let ((x (myinsert N (cdr L))))
(if (> (car L) N) (cons N L)
(cons (car L) x)))))

;;;Solution to proble 5
(defun my_isort (L)
(if (endp L)
nil
(let ((x (my_isort (cdr L))))
(insert (car L) x))))

;;;Solution to proble 6
(defun my_split_list (L)
(if (endp L)
(list nil nil)
(let ((x (my_split_list (cdr L))))
(list (cons (car L) (cadr x)) (car x)))))

;;;Solution to proble 7
(defun my_partition (L N)
(cond ((endp L)
(list nil nil))
((< (car L) N)
(list (cons (car L) (car (my_partition (cdr L) N))) (cadr (my_partition (cdr L) N))))
(t(list (car (my_partition(cdr L) N)) (cons (car L) (cadr (my_partition (cdr L) N)))))))

;;;Solution to proble 8
(defun POS (E L)
(cond ((endp L) 0)
((equal E (car L)) 1)
(T (let ((X (POS E (cdr L))))
(+ X 1)))))

;;;Solution to proble 9
(defun split-nums (E)
(cond ((<= E 0) nil)
(t (let ((x (split-nums (- E 1))))
(if (oddp E)
(list (cons E (car x))(cadr x))
(list (car x) (cons E (cadr x))))))))

;;;Solution to proble 10
(defun set-union (s1 s2)
(cond ((endp s1) s2)
((endp s2) s1)
(t (let ((x (set-union (cdr s1) s2)))
(if (equal (car s1) x) x
(cons (car s1) x))))))

;;;Solution to proble 11
(defun my-set-remove (X S) 
(cond ((endp s) nil)
(T (let ((z (my-set-remove X (cdr s))))
(if (equal (car s) x)
z
(cons (car s) z))))))

;;;Solution to proble 12
(defun set-excl-union (s1 s2)
(cond ((endp s1) s2)
((endp s2) s1)
(t (let ((x (set-excl-union (cdr s1)s2)))
(if (member (car s1) x)
(my-set-remove(car s1) s2)
(cons (car s1) x))))))

;;;Solution to proble 13
(defun singletons (e)
(cond ((endp e) nil)
((member (car e) (cdr e))
(my-set-remove (car e)
(singletons (cdr e))))
(t (cons (car e) (singletons (cdr e))))))