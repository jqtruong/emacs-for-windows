;; Convert cl to cups.
(defun cl-to-cups (cl)
  ""
  (interactive "nCentiliters: ")
  (let ((oz (* 60 0.338140227)))
    (message "%f" (* oz .125))))
