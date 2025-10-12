
> [!warning] API Key
> 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

```python
from openai import OpenAI

client = OpenAI(
  base_url = "https://integrate.api.nvidia.com/v1",
  api_key = "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"
)

completion = client.chat.completions.create(
  model="writer/palmyra-med-70b",
  messages=[{"role":"user","content":""}],
  temperature=0.2,
  top_p=0.7,
  max_tokens=1024,
  stream=True
)

for chunk in completion:
  if chunk.choices[0].delta.content is not None:
    print(chunk.choices[0].delta.content, end="")

```
