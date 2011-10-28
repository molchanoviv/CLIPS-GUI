(autoload 'clips-mode "clips-mode" "Clips editing mode." t)
(autoload 'run-clips "inf-clips" "Run Clips." t)
(add-to-list 'auto-mode-alist '("\\.clp$" . clips-mode))
