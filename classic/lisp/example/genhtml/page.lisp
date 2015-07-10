(defparameter *section* nil)

(defstruct item
  id title text)

(defstruct section
  id title items)

(defmacro defitem (id title text)
  '(setf ,id
         (make-item :id    ',id
                    :title ,title
                    :text  ,text)))

(defmacro defsection (id title &rest items)
  '(setf ,id
         (make-section :id    ',id
                       :title ,title
                       :items (list ,@items))))

(defun defsite (&rest sections)
  (setf *sections* sections))
