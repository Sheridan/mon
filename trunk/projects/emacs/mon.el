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
(set-language-environment "UTF-8")
(set-default-coding-systems 'utf-8)
(global-set-key (kbd "<f3>") 'semantic-ia-fast-jump)
(message "Loading project mon [%s]" default-directory)
(message "Searching packages")
;;(setq cmake-mode-el-file (shell-command-to-string "locate --basename --regexp \"cmake-mode.el$\" | grep \"/usr/share\""))

(message "Loading packages")
(add-to-list 'load-path (concat default-directory "projects/emacs/packages/CEDET/source"))
(add-to-list 'load-path (concat default-directory "projects/emacs/packages/ECB/source"))
(add-to-list 'load-path (concat default-directory "projects/emacs/packages/popup/source"))
(add-to-list 'load-path (concat default-directory "projects/emacs/packages/auto-complete/source"))
(add-to-list 'load-path (concat default-directory "projects/emacs/packages/dash/source"))
(add-to-list 'load-path (concat default-directory "projects/emacs/packages/json-mode/source"))
(add-to-list 'load-path (concat default-directory "projects/emacs/packages/json-reformat/source"))
(add-to-list 'load-path (concat default-directory "projects/emacs/packages/json-snatcher/source"))


(message "Turning on CEDET")
(load-file (concat default-directory "projects/emacs/packages/CEDET/source/cedet-devel-load.el"))
(global-ede-mode t)

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

(message "Turning on Semantic")
(add-to-list 'semantic-default-submodes 'global-semantic-idle-summary-mode t)
(add-to-list 'semantic-default-submodes 'global-semantic-idle-completions-mode t)
(add-to-list 'semantic-default-submodes 'global-cedet-m3-minor-mode t)
(setq semanticdb-default-save-directory (concat default-directory "projects/emacs/semanticdb/mon"))
(setq auto-update-methods-after-save t)
(semanticdb-enable-gnu-global-databases 'c-mode)
(semanticdb-enable-gnu-global-databases 'c++-mode)
(semantic-load-enable-gaudy-code-helpers)
(semantic-load-enable-excessive-code-helpers)
(semantic-load-enable-semantic-debugging-helpers)
(semantic-mode t)

(message "Turning on popup")
(require 'popup)

(message "Turning on auto-complete")
(require 'auto-complete)
(require 'auto-complete-config)
(ac-config-default)

(message "Turning on dash")
(require 'dash)

(message "Making hooks")
(defun autocomplete-semantic-modes-cedet-hook ()
  (add-to-list 'ac-sources 'ac-source-gtags)
  (add-to-list 'ac-sources 'ac-source-semantic))
(add-hook 'c-mode-common-hook 'autocomplete-semantic-modes-cedet-hook)

(defun semantic-modes-cedet-hook ()
  (add-to-list 'ac-sources 'ac-source-gtags)
  (add-to-list 'ac-sources 'ac-source-semantic))
(add-hook 'c-mode-common-hook 'semantic-modes-cedet-hook)

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

(message "Loading themes")
(add-to-list 'custom-theme-load-path (concat default-directory "projects/emacs/themes/solarized/source"))
(add-to-list 'load-path (concat default-directory "projects/emacs/themes/solarized/source"))
(setq solarized-termcolors 256)
(set-frame-parameter nil 'background-mode 'dark)
(set-terminal-parameter nil 'background-mode 'dark)
(load-theme 'solarized t)

(message "Loding project directoryes")
(setq mon-src-directoryes (append ["/application"] (directory-dirs "application") (directory-dirs "sensors")))
(setq system-include-directoryes (split-string (shell-command-to-string "echo | gcc -Wp,-v -x c++ - -fsyntax-only 2>&1 | grep \"/include$\"")))

;;(prin1 system-include-directoryes)
(message "Loding project")
(ede-cpp-root-project "mon" :directory default-directory :file "linux-build"
     :system-include-path system-include-directoryes
     :include-path mon-src-directoryes
     :compile-command  "./linux-build -d -v -c"
     )

(message "Done")
