from urllib.parse import urlparse, parse_qs
import sys

def parse_token(token_url):
    parsed = urlparse(token_url)
    query_params = parse_qs(parsed.query)
    return {
        'host': parsed.hostname,
        'port': parsed.port,
        'path': parsed.path,
        'query': {k: v[0] for k, v in query_params.items()}
    }

def compare_tokens(cli_token, cpp_token):
    token1 = parse_token(cli_token)
    token2 = parse_token(cpp_token)

    print("== Host Match:", token1['host'] == token2['host'])
    print("== Port Match:", token1['port'] == token2['port'])
    print("== Path Match:", token1['path'] == token2['path'])

    for key in token1['query']:
        if key in token2['query']:
            if token1['query'][key] == token2['query'][key]:
                print(f"[✓] {key} matches")
            else:
                print(f"[~] {key} differs:\n   CLI: {token1['query'][key]}\n   CPP: {token2['query'][key]}")
        else:
            print(f"[✗] {key} not in CPP token")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python compare_rds_tokens.py <cli_token_url> <cpp_token_url>")
        sys.exit(1)

    cli_token = sys.argv[1]
    cpp_token = sys.argv[2]

    compare_tokens(cli_token, cpp_token)
