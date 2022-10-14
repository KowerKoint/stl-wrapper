function! OJD(url) abort
  execute "Deol -split=float zsh oj-download.sh " . a:url
  if fnamemodify(a:url, ":h:t") == "contests"
    let @a = "Contests/AtCoder_" . fnamemodify(a:url, ":t") . "/*/main.cpp"
  else
    let @a = "Contests/AtCoder_" . fnamemodify(a:url, ":h:h:t") . "/" . fnamemodify(a:url, ":t") . "/main.cpp"
  endif
endfunction
command! -nargs=1 OJD call OJD(<f-args>)

function! CreateSolution(dirpath) abort
  call system('mkdir ' . a:dirpath)
  call system('cp template/template.cpp ' . a:dirpath . "/main.cpp")
  let @a = a:dirpath . "/main.cpp"
endfunction
command! -nargs=1 CreateSolution call CreateSolution(<f-args>)
  

nnoremap <expr> <Leader>o ":<C-u>argadd " . @a
nnoremap <Leader>d :<C-u>OJD 
nnoremap <expr> <Leader>b ":<C-u>Deol -split=float zsh oj-test.sh build " . expand("%")
nnoremap <expr> <Leader>t ":<C-u>Deol -split=float zsh oj-test.sh test " . expand("%")
nnoremap <expr> <Leader>s ":<C-u>Deol -split=float zsh oj-test.sh submit " . expand("%")
nnoremap <expr> <Leader>f ":<C-u>Deol -split=float zsh oj-test.sh force-submit " . expand("%")
nnoremap <expr> <Leader>r ":<C-u>Deol -split=float " . expand("%:r")
nnoremap <expr> <Leader>g ":<C-u>Deol -split=float gdb " . expand("%:r")
nnoremap <expr> <Leader>e ":<C-u>e " . expand("%:r") . "_expanded.cpp"
nnoremap <expr> <Leader>c ":<C-u>CreateSolution "
nnoremap <Leader>] :<C-u>next<CR>
nnoremap <Leader>[ :<C-u>prev<CR>
