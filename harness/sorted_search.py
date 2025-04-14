def execute_program(timeout: int) -> tuple[str, int]:
    import signal
    import os
    import subprocess
    import tempfile

    # Create a temporary file
    with tempfile.NamedTemporaryFile(mode="w") as temp_file:
        temp_file.write("1.0 2.0 3.0 4.0 5.0 2.000")
        temp_file.flush()
        temp_file_path = temp_file.name

        try:
            result = subprocess.run(
                ["./program", temp_file_path],
                capture_output=True,
                encoding="utf-8",
                errors="replace",
                timeout=timeout,
            )
            # Return stderr and the return code
            return result.stderr, result.returncode
        except subprocess.TimeoutExpired as e:
            # Timeout occurred, also ensure to return stderr captured before timeout and return code -signal.SIGKILL
            return e.stderr, -signal.SIGKILL
        except Exception as e:
            # ensure to raise the error if run failed
            raise e
