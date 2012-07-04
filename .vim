let g:vim_ignore += [
                      \ 'bin',
                      \ 'build',
                      \ 'doc',
                      \ 'tmp',
                      \ 'tools/nc111nt',
                      \ 'vendor',
                   \]
let g:vim_other += [
                      \ '/usr/local/Cellar/avr-libc/1.7.1/avr/include/',
                   \]
set wildignore+=bin,build,doc,tmp,tools/nc111nt,vendor
