;; -------------------- functions -------------------------
(defun directory-dirs (dir)
    "Find all directories in DIR."
    (unless (file-directory-p dir)
      (error "Not a directory `%s'" dir))
    (let ((dir (directory-file-name dir))
          (dirs '())
          (files (directory-files dir nil nil t)))
        (dolist (file files)
          (unless (member file '("." ".."))
            (let ((file (concat (file-name-as-directory dir) file)))
              (when (file-directory-p file)
                (let ((tdir (concat "/" file)))
                (message "Progect sourcr directory (%s)" tdir)
                (setq dirs (append (cons tdir
                                         (directory-dirs file))
                                   dirs)))))))
        dirs))

;; -------------------- init -------------------------
(message "Preinit...")
;;(async-shell-command (concat default-directory "projects/emacs/packages/rtags/source/bin/rdm"))
(start-process "rdm" "*rtags rdm output*" (concat default-directory "projects/emacs/packages/rtags/source/bin/rdm"))
;;(sleep-for 3)
(start-process "rc" "*rtags rc output*" (concat default-directory "projects/emacs/packages/rtags/source/bin/rc") "-v" "-J" (concat default-directory "projects/emacs/storage/rtags/compile_commands.json"))
;;(shell-command (concat default-directory "projects/emacs/packages/rtags/source/bin/rc -v -J " default-directory "projects/emacs/storage/rtags/compile_commands.json"))
(add-hook 'kill-emacs-hook (lambda () (kill-process "rdm")))
(set-language-environment "UTF-8")
(set-default-coding-systems 'utf-8)

(message "Loading project mon [%s]" default-directory)
(message "Loding project directoryes")
(setq mon-src-directoryes (append ["/application"] (directory-dirs "application") (directory-dirs "sensors")))
(setq system-include-directoryes (split-string (shell-command-to-string "echo | gcc -Wp,-v -x c++ - -fsyntax-only 2>&1 | grep \"/include$\"")))
(message "Searching packages")
;;(setq cmake-mode-el-file (shell-command-to-string "locate --basename --regexp \"cmake-mode.el$\" | grep \"/usr/share\""))

(message "Setting load-paths")
(let ((pkgs 
	'(
		"CEDET" 
		"ECB" 
		"yasnippet" 
;;		"popup" 
		"auto-complete" 
		"auto-complete-clang" 
		"dash" 
		"which-key" 
		"company" 
		"json-mode" 
		"json-reformat" 
		"json-snatcher" 
		"color-theme-approximate" 
;;		"rtags"
		"linum-higlite-current-line"
	)))
	(while pkgs
	    (add-to-list 'load-path (concat default-directory "projects/emacs/packages/" (pop pkgs) "/source") )))

(add-to-list 'load-path (concat default-directory "projects/emacs/packages/rtags/source/src"))
(add-to-list 'exec-path (concat default-directory "projects/emacs/packages/rtags/source/bin"))

;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Turning on CEDET")
(load-file (concat default-directory "projects/emacs/packages/CEDET/source/cedet-devel-load.el"))
(global-ede-mode t)
;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Turning on ECB")
(require 'ecb)
(setq ecb-auto-activate t)
(setq ecb-show-sources-in-directories-buffer 'always)
(setq ecb-layout-name "left15")
(defun sheridan/ecb-hide-ecb-windows ()
  "hide ecb and then split emacs into 2 windows that contain 2 most recent buffers"
  (interactive)
  (ecb-hide-ecb-windows)
  (other-window 1))
(defun sheridan/ecb-show-ecb-windows ()
  "show ecb windows and then delete all other windows except the current one"
  (interactive)
  (ecb-show-ecb-windows)
  (delete-other-windows)
  (ecb-goto-window-directories))
(global-set-key (kbd "<C-home>") 'sheridan/ecb-show-ecb-windows)
(global-set-key (kbd "<C-end>") 'sheridan/ecb-hide-ecb-windows)
;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Turning on Yasnippet")
(require 'yasnippet)
(setq yas-snippet-dirs '())
(add-to-list 'yas-snippet-dirs  (concat default-directory "projects/emacs/snippets"))
(add-to-list 'yas-snippet-dirs  (concat default-directory "projects/emacs/packages/yasnippet/source"))
(yas-reload-all)
(add-hook 'prog-mode-hook #'yas-minor-mode)
;;(yas-global-mode t)
;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Turning on Semantic")
(add-to-list 'semantic-default-submodes 'global-semantic-idle-summary-mode t)
(add-to-list 'semantic-default-submodes 'global-semantic-idle-completions-mode t)
(add-to-list 'semantic-default-submodes 'global-cedet-m3-minor-mode t)
(setq semanticdb-default-save-directory (concat default-directory "projects/emacs/storage/semanticdb"))
(setq auto-update-methods-after-save t)
(semanticdb-enable-gnu-global-databases 'c-mode)
(semanticdb-enable-gnu-global-databases 'c++-mode)
(semantic-load-enable-gaudy-code-helpers)
(semantic-load-enable-excessive-code-helpers)
(semantic-load-enable-semantic-debugging-helpers)
(global-set-key (kbd "<f3>") 'semantic-ia-fast-jump)
;;(semantic-mode t)
;; ---------------------------------------------------------------------------------------------------------------------------------------------
;;(message "Turning on popup")
;;(require 'popup)
;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Turning on which-key")
(require 'which-key)
;;(which-key-setup-side-window-right)
(which-key-setup-minibuffer)
(add-to-list 'which-key-key-replacement-alist '("TAB" . "↹"))
(add-to-list 'which-key-key-replacement-alist '("RET" . "⏎"))
(add-to-list 'which-key-key-replacement-alist '("DEL" . "⇤"))
(add-to-list 'which-key-key-replacement-alist '("SPC" . "␣"))
(which-key-mode t)

;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Turning on rtags")
(require 'rtags)

;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Turning on company")
(require 'company)
(require 'company-semantic)
(require 'company-yasnippet)
(require 'company-clang)
(require 'company-cmake)
(require 'company-rtags)
(require 'company-keywords)
(add-hook 'prog-mode-hook #'company-mode)
;;(add-hook 'c-mode-common-hook (lambda () (setq company-backends '(company-rtags))))
;; ---------------------------------------------------------------------------------------------------------------------------------------------
;;(message "Turning on auto-complete")
;;(require 'auto-complete)
;;(require 'auto-complete-config)
;;(require 'auto-complete-clang)
;;(setq ac-auto-start nil)
;;(setq ac-quick-help-delay 0.5)
;;(define-key ac-mode-map  [(control tab)] 'auto-complete)
;;(defun my-ac-config ()
;;  (setq-default ac-sources '(ac-source-abbrev ac-source-dictionary ac-source-words-in-same-mode-buffers))
;;  ;;(add-hook 'emacs-lisp-mode-hook 'ac-emacs-lisp-mode-setup)
;;  (add-hook 'c-mode-common-hook 'ac-cc-mode-setup)
;;  ;;(add-hook 'ruby-mode-hook 'ac-ruby-mode-setup)
;;  ;;(add-hook 'css-mode-hook 'ac-css-mode-setup)
;;  (add-hook 'auto-complete-mode-hook 'ac-common-setup)
;;  (global-auto-complete-mode t))
;;(defun my-ac-cc-mode-setup ()
;;  (setq ac-sources (append '(ac-source-clang ac-source-yasnippet) ac-sources)))
;;(add-hook 'c-mode-common-hook 'my-ac-cc-mode-setup)
;;;; ac-source-gtags
;;(setq ac-clang-flags
;;      (mapcar (lambda (item)(concat "-I" item))
;;              system-include-directoryes))
;;(my-ac-config)
;;(ac-config-default)
;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Turning on dash")
(require 'dash)
;; ---------------------------------------------------------------------------------------------------------------------------------------------
;;(message "Making hooks")
;;(defun autocomplete-semantic-modes-cedet-hook ()
;;  (add-to-list 'ac-sources 'ac-source-gtags)
;;  (add-to-list 'ac-sources 'ac-source-semantic))
;;(add-hook 'c-mode-common-hook 'autocomplete-semantic-modes-cedet-hook)
;;
;;(defun semantic-modes-cedet-hook ()
;;  (add-to-list 'ac-sources 'ac-source-gtags)
;;  (add-to-list 'ac-sources 'ac-source-semantic))
;;(add-hook 'c-mode-common-hook 'semantic-modes-cedet-hook)

(add-hook 'c-mode-common-hook
  (lambda() 
    (local-set-key  (kbd "<f4>") 'ff-find-other-file)))

(setq auto-mode-alist
      (append
       '(("CMakeLists\\.txt\\'" . cmake-mode))
       '(("\\.cmake\\'" . cmake-mode))
       auto-mode-alist))

;;(prin1 cmake-mode-el-file)
(autoload 'cmake-mode "cmake-mode.el" t)

(setq auto-mode-alist
      (append
       '(("\\.conf\\'" . json-mode))
       auto-mode-alist))
(autoload 'json-mode "json-mode.el" t)


;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Lines numbering setup")
(load-file (concat default-directory "projects/emacs/packages/linum-higlite-current-line/source/linum-highligth-current-line-number.el"))
(setq linum-right-border-width 1)
(add-hook 'prog-mode-hook 'linum-mode)
;; ---------------------------------------------------------------------------------------------------------------------------------------------
(message "Loading themes")
(load-file (concat default-directory "projects/emacs/packages/color-theme-approximate/source/color-theme-approximate.el"))
(color-theme-approximate-on)
(add-to-list 'custom-theme-load-path (concat default-directory "projects/emacs/themes/solarized/source"))
(add-to-list 'load-path (concat default-directory "projects/emacs/themes/solarized/source"))
(setq solarized-termcolors 256)
(set-frame-parameter nil 'background-mode 'dark)
(set-terminal-parameter nil 'background-mode 'dark)
(load-theme 'solarized t)


;; gdb -cd directory
;;(prin1 system-include-directoryes)
(message "Loding project")
(ede-cpp-root-project "mon" :directory default-directory :file "linux-build"
     :system-include-path system-include-directoryes
     :include-path mon-src-directoryes
     :compile-command  "./linux-build -d -v -c -e"
     )

(message "Done")
