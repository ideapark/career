(dl-list 'a 'b 'c)
(dl-insert 'a (dl-insert 'b (dl-insert 'c nil)))

(setf dl (dl-list 'a 'b))
(setf dl (dl-insert 'c dl))

(dl-insert 'r (dl-next dl))
dl
