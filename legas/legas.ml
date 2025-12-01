let app = "ejs"
let orig = "ref/2v25"
let title = "Espruino /vibe"
let author = "Dmitry Ponyatov"
let email = "dponyatov@gmail.com"
let year = 2025
let license = "MIT"

let touch name ?(c = "") () =
  (* if not (Sys.file_exists name) then *)
  let f = open_out name in
  output_string f c;
  close_out f

let mkd name ?(c = "!.gitignore\n") () =
  if not (Sys.file_exists name) then Sys.mkdir name 0o755;
  touch (name ^ "/.gitignore") ~c ()

let dirs () =
  [ ".vscode"; "bin"; "lib"; "inc"; "src"; "tmp"; "ref" ]
  |> List.iter (fun d -> mkd d ())

let bins () =
  [ "bin"; "tmp"; "ref" ] |> List.iter (fun d -> mkd d ~c:"*\n!.gitignore\n" ())

let doc () = mkd "doc" ~c:"html/\n!.gitignore\n" ()

let giti () = touch ".gitignore" ~c:"*~
*.swp
*.log
!.gitignore
" ()

let mk () =
  touch "Makefile" ()

  let vibe0 () = 
    (* iterate over ref/${ref} 
    - touch files not exists
    - mkdir dirs not exists
    - skip dirs: .git *)