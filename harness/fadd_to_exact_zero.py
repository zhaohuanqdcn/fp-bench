def execute_program() -> tuple[str, int]:
    import subprocess

    try:
        result = subprocess.run(
            ["./program 1.0 -1.0 3"],
            capture_output=True,
            shell=True,
            encoding="utf-8",
            errors="replace",
        )
        # Return stderr and the return code
        return result.stderr, result.returncode
    except Exception as e:
        # ensure to raise the error if run failed
        raise e
