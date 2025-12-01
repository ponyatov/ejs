let app = "ejs"
let title = "Espruino /vibe"
let author = "Dmitry Ponyatov"
let email = "dponyatov@gmail.com"
let year = 2025
let license = "MIT"

let touch name ?(c = "") () =
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

let doc () =
  mkd "doc" ~c:"html/\n!.gitignore\n" ()

let giti () = touch ".gitignore" "*~
*.swp
*.log
!.gitignore
"
