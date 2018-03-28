set nocompatible
filetype off  

colorscheme solarized

set nu
set backspace=2
set shortmess=atI

syntax on

set lines=35 columns=118
set guifont=Source_Code_Pro:h16

set laststatus=2
set noshowmode
set guioptions-=r
set autochdir

set nobackup

set confirm

set mouse=a

set tabstop=4
set shiftwidth=4
set expandtab
set smarttab

set autoread

set cindent

set autoindent

set smartindent

set hlsearch

set background=dark

set ruler


set novisualbell

autocmd InsertLeave * se nocul

autocmd InsertEnter * se cul

set showcmd

set fillchars=vert:/

set fillchars=stl:/

set fillchars=stlnc:/


call plug#begin('~/.vim/plugged')
Plug 'junegunn/limelight.vim'
Plug 'junegunn/goyo.vim'
Plug 'junegunn/vim-easy-align'
Plug 'itchyny/lightline.vim'
call plug#end()

autocmd! User GoyoEnter Limelight
autocmd! User GoyoLeave Limelight!

nnoremap <F8>   <Esc>:w<CR>:Goyo<CR>
vnoremap <F8>   <Esc>:w<CR>:Goyo<CR>
inoremap <F8>   <Esc>:w<CR>:Goyo<CR>

nnoremap <F5>   <Esc>:w<CR>:!g++ -std=c++11 % -o /tmp/a.out && /tmp/a.out<CR>
inoremap <F5>   <Esc>:w<CR>:!g++ -std=c++11 % -o /tmp/a.out && /tmp/a.out<CR>
vnoremap <F5>   <Esc>:w<CR>:!g++ -std=c++11 % -o /tmp/a.out && /tmp/a.out<CR>

nnoremap <F6> <Esc>:w<CR>:!g++ -std=c++11 -g % -o /tmp/a.out && lldb /tmp/a.out<CR>
inoremap <F6> <Esc>:w<CR>:!g++ -std=c++11 -g % -o /tmp/a.out && lldb /tmp/a.out<CR>
vnoremap <F6> <Esc>:w<CR>:!g++ -std=c++11 -g % -o /tmp/a.out && lldb /tmp/a.out<CR>

inoremap <D-[> <Esc> 
nnoremap <D-[> i

inoremap jj <Esc>
