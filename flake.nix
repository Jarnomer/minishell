{
  description = "Minishell Development Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      ...
    }@inputs:
    inputs.flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            gcc
            gnumake
            valgrind
            norminette
            coreutils
            bash
            readline
          ];

          shellHook = ''
            printf "Minishell development environment loaded!\n"
            trap 'make fclean' EXIT
          '';
        };
      }
    );
}
