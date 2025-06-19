import torch
import torch.nn as nn
import torch.optim as optim


# XOR input and output data
X = torch.tensor([
    [0, 0],
    [0, 1],
    [1, 0],
    [1, 1]
], dtype=torch.float32)

Y = torch.tensor([
    [0],
    [1],
    [1],
    [0]
], dtype=torch.float32)

# Define a simple feedforward network with 1 hidden layer
class XORNet(nn.Module):
    def __init__(self):
        super(XORNet, self).__init__()
        self.net = nn.Sequential(
            nn.Linear(2, 4),   # 2 inputs -> 4 hidden units
            nn.Tanh(),         # nonlinear activation
            nn.Linear(4, 1),   # 4 hidden -> 1 output
            nn.Sigmoid()       # sigmoid to map to [0,1]
        )

    def forward(self, x):
        return self.net(x)

# Initialize model, loss, optimizer
model = XORNet()
criterion = nn.BCELoss()               # Binary Cross Entropy
optimizer = optim.Adam(model.parameters(), lr=0.1)

# Training loop
for epoch in range(10000):
    y_pred = model(X)
    loss = criterion(y_pred, Y)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    if epoch % 1000 == 0:
        print(f"Epoch {epoch}, Loss: {loss.item():.4f}")

# Test results
with torch.no_grad():
    print("\nFinal predictions:")
    preds = model(X)
    print(torch.round(preds))  # Round to 0 or 1