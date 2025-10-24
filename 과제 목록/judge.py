import zipfile
import os
import subprocess
import sys
import tempfile

def extract_zip(zip_path, extract_to):
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(extract_to)

def find_test_cases(folder):
    inp_files = [f for f in os.listdir(folder) if f.endswith('.inp')]
    test_cases = []
    for inp in inp_files:
        base = inp[:-4]
        out = base + '.out'
        if out in os.listdir(folder):
            test_cases.append((os.path.join(folder, inp), os.path.join(folder, out)))
    return test_cases

def run_code(code_path, inp_path):
    ext = os.path.splitext(code_path)[1]
    if ext == '.py':
        with open(inp_path, 'r') as inp_file:
            try:
                result = subprocess.run(
                    [sys.executable, code_path],
                    stdin=inp_file,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    timeout=5
                )
                return result.stdout.decode().strip()
            except Exception as e:
                return f"Error: {e}"
    elif ext == '.cpp':
        exe_path = code_path + '.exe'
        compile_result = subprocess.run(
            ['g++', code_path, '-o', exe_path],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        if compile_result.returncode != 0:
            return f"컴파일 오류: {compile_result.stderr.decode()}"
        try:
            with open(inp_path, 'r') as inp_file:
                result = subprocess.run(
                    [exe_path],
                    stdin=inp_file,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    timeout=5
                )
                return result.stdout.decode().strip()
        except Exception as e:
            return f"Error: {e}"
        finally:
            if os.path.exists(exe_path):
                os.remove(exe_path)
    else:
        return "지원하지 않는 코드 파일 형식입니다. (.py 또는 .cpp만 지원)"

def compare_output(output, out_path):
    with open(out_path, 'r') as out_file:
        expected = out_file.read()
    # 줄 단위로 strip 후 비교
    output_lines = [line.strip() for line in output.splitlines()]
    expected_lines = [line.strip() for line in expected.splitlines()]
    return output_lines == expected_lines, expected

def main():
    if len(sys.argv) != 3:
        print("사용법: python judge.py <테스트케이스 zip파일> <코드파일.py|cpp>")
        print("예시: python judge.py cases.zip solution.py")
        print("예시: python judge.py cases.zip solution.cpp")
        print("\n- zip파일에는 여러 개의 .inp/.out 쌍이 들어있어야 합니다.")
        print("- 코드파일은 표준 입력(stdin)으로 입력을 받아 표준 출력(stdout)으로 결과를 출력해야 합니다.")
        print("- 각 .inp 파일이 입력으로, .out 파일이 정답으로 사용됩니다.")
        return

    zip_path = sys.argv[1]
    code_path = sys.argv[2]

    with tempfile.TemporaryDirectory() as tempdir:
        extract_zip(zip_path, tempdir)
        test_cases = find_test_cases(tempdir)
        if not test_cases:
            print("테스트 케이스를 찾을 수 없습니다.")
            return

        correct_count = 0
        wrong_count = 0

        for idx, (inp, out) in enumerate(test_cases, 1):
            output = run_code(code_path, inp)
            correct, expected = compare_output(output, out)
            print(f"[테스트케이스 {idx}]: {'정답' if correct else '오답'}")
            if correct:
                correct_count += 1
            else:
                wrong_count += 1
                print(f"입력파일: {os.path.basename(inp)}")
                print("기대값:")
                print(expected)
                print("출력값:")
                print(output)
            print()  # 각 테스트케이스 사이 줄바꿈

        print(f"정답: {correct_count}개")
        print(f"오답: {wrong_count}개")

if __name__ == "__main__":
    main()
