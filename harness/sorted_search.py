def execute_program() -> tuple[str, int]:
    import os
    import subprocess
    import tempfile

    # Create a temporary file
    with tempfile.NamedTemporaryFile(mode="w", delete=False) as temp_file:
        temp_file.write("1.0 2.0 3.0 4.0 5.0 2.000")
        temp_file_path = temp_file.name

    try:
        result = subprocess.run(
            ["./program", temp_file_path],
            capture_output=True,
            encoding="utf-8",
            errors="replace",
        )
        # Return stderr and the return code
        return result.stderr, result.returncode
    except Exception as e:
        # ensure to raise the error if run failed
        raise e
    finally:
        # Clean up the temporary file
        if os.path.exists(temp_file_path):
            os.remove(temp_file_path)
